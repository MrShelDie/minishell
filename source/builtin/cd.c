/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:13:42 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 18:17:20 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "minishell.h"
#include <limits.h>
#include <stdlib.h>

int	exec_double_minus(char *new_cwd, char *cwd, t_shell_data *data, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	if (map_add(data->env_map, "OLDPWD", cwd) == FAIL)
		return (FAIL);
	if (vector_add(data->env_vector, cwd) == FAIL)
		return (FAIL);
	if (map_add(data->env_map, "PWD", new_cwd) == FAIL)
		return (FAIL);
	if (vector_add(data->env_vector, new_cwd) == FAIL)
		return (FAIL);
	if (chdir(new_cwd) == -1)
		return (FAIL);
	free(new_cwd);
	return (SUCCESS);
}

int	double_minus(char *cwd, t_shell_data *data, char *new_cwd)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_split(cwd, '/');
	while (tmp[i])
		i++;
	new_cwd = (char *)malloc(sizeof(char) * 2);
	new_cwd[0] = '/';
	new_cwd[1] = '\0';
	while (j < i - 1)
	{
		new_cwd = ft_strjoin(new_cwd, tmp[j]);
		if (j != i - 2)
			new_cwd = ft_strjoin(new_cwd, "/");
		j++;
	}
	if (exec_double_minus(new_cwd, cwd, data, tmp) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	next_exec_minus(t_shell_data *data, char *cwd, \
					char *new_cwd, int option)
{
	if (option == 1)
	{
		if (one_minus(cwd, data, new_cwd) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	else if (option == 2)
	{
		if (double_minus(cwd, data, new_cwd) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	return (3);
}

int	ft_cd(char **av, t_shell_data *shell_data)
{
	char		cwd[PATH_MAX];
	char		*new_cwd;
	int			check_args;
	int			option;

	new_cwd = NULL;
	if (check_arg(av, &check_args, &option) == FAIL)
		return (FAIL);
	getcwd(cwd, PATH_MAX);
	if (check_args > 0)
	{
		option = next_exec_minus(shell_data, cwd, new_cwd, option);
		if (option == FAIL)
			return (FAIL);
		else if (option == SUCCESS)
			return (SUCCESS);
	}
	map_add(shell_data->env_map, "OLDPWD", cwd);
	vector_add(shell_data->env_vector, cwd);
	map_add(shell_data->env_map, "PWD", av[1]);
	if (chdir(av[1]) == -1)
		return (FAIL);
	return (SUCCESS);
}
