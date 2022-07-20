/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:34:50 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 17:40:08 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/builtins.h"
#include "../../include/minishell.h"

void	ft_strcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < (size - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	check_arg(char **av, int *check, int *option)
{
	int			i;

	i = 1;
	*check = 0;
	*option = 0;
	if (ft_strncmp(av[i], "-", 1) == 0)
		*option = 1;
	if (ft_strncmp(av[i], "--", 2) == 0)
		*option = 2;
	while (av[i])
	{
		if (ft_strncmp(av[i], "-", 1) == 0)
			(*check)++;
		else if (ft_strncmp(av[i], "--", 2) == 0)
			(*check)++;
		i++;
	}
	if ((*check) > 1)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 1);
		return (FAIL);
	}
	return (SUCCESS);
}

int	one_minus(char *cwd, t_shell_data *data, char *new_cwd)
{
	int	lenght;

	lenght = ft_strlen(map_get(data->env_map, "HOME"));
	if (map_add(data->env_map, "OLDPWD", cwd) == FAIL)
		return (FAIL);
	if (vector_add(data->env_vector, cwd) == FAIL)
		return (FAIL);
	new_cwd = (char *)malloc(sizeof(char) * (lenght + 1));
	ft_strcpy(new_cwd, map_get(data->env_map, "HOME"), (lenght + 1));
	if (map_add(data->env_map, "PWD", new_cwd) == FAIL)
		return (FAIL);
	if (vector_add(data->env_vector, new_cwd) == FAIL)
		return (FAIL);
	chdir(new_cwd);
	free(new_cwd);
	return (SUCCESS);
}
