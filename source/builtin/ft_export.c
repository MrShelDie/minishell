/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 22:58:22 by medric            #+#    #+#             */
/*   Updated: 2022/08/02 19:11:01 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	putstr(int len, char **map_buff)
{
	int		i;

	i = -1;
	while (++i < len)
		printf("declare -x %s\n", map_buff[i]);
}

int	print_sort_env(t_vector *map)
{
	char	**map_buff;
	char	**value;
	int		err;

	err = 0;
	value = NULL;
	map_buff = NULL;
	map_buff = create_buff(map_buff, map, &err);
	if (err == 1)
	{
		delete_buff(map_buff, map->length);
		return (FAIL);
	}
	map_buff = sort_buff(map_buff, map->length);
	putstr((int)map->length, map_buff);
	delete_buff(map_buff, map->length);
	return (SUCCESS);
}

int	add_data(t_shell_data *data, t_vector *cmd)
{
	char	**tmp;
	int		i;

	i = 1;
	tmp = NULL;
	if (ft_searchr(cmd->data[i], '=') == 0)
	{
		if (vector_add(data->env_vector, cmd->data[i]) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	tmp = ft_split(cmd->data[i], '=');
	if (!tmp)
		return (FAIL);
	if (map_add(data->env_map, tmp[0], tmp[1]) == FAIL)
		return (FAIL);
	if (vector_add(data->env_vector, cmd->data[i]) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	ft_export(t_shell_data *data, t_vector *cmd)
{
	if (cmd->length < 2)
	{
		if (print_sort_env(data->env_vector) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	if (add_data(data, cmd) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
