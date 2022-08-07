/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:13:42 by medric            #+#    #+#             */
/*   Updated: 2022/08/07 21:48:15 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static int	double_minus_error(char **tmp, int *i, char *cwd, char *new_cwd)
{
	tmp = ft_split(cwd, '/');
	if (!tmp)
	{
		print_error(strerror(errno));
		return (FAIL);
	}
	while (tmp[*i])
		(*i)++;
	new_cwd = (char *)malloc(sizeof(char) * 2);
	if (!new_cwd)
	{
		print_error(strerror(errno));
		return (FAIL);
	}	
	new_cwd[0] = '/';
	new_cwd[1] = '\0';
	return (SUCCESS);
}

int	double_minus(char *cwd, t_shell_data *data, char *new_cwd)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = NULL;
	if (!double_minus_error(tmp, &i, cwd, new_cwd))
		return (FAIL);
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

int	add_to_map_and_vector(t_shell_data *shell_data, char *cwd, char *cmd)
{
	map_add(shell_data->env_map, "OLDPWD", cwd);
	vector_add(shell_data->env_vector, cwd);
	map_add(shell_data->env_map, "PWD", cmd);
	if (chdir(cmd) == -1)
	{
		print_error(strerror(errno));
		return (errno);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd(t_shell_data *shell_data, t_vector *cmd)
{
	char		cwd[PATH_MAX];
	char		*new_cwd;
	int			check_args;
	int			option;

	new_cwd = NULL;
	if (cmd->length < 2)
		return (EXIT_SUCCESS);
	if (check_arg(cmd->data, &check_args, &option) == FAIL)
		return (EXIT_FAILURE);
	getcwd(cwd, PATH_MAX);
	if (check_args > 0)
	{
		option = next_exec_minus(shell_data, cwd, new_cwd, option);
		if (option == FAIL)
			return (EXIT_FAILURE);
		else if (option == SUCCESS)
			return (EXIT_SUCCESS);
	}
	return (add_to_map_and_vector(shell_data, cwd, cmd->data[1]));
}
