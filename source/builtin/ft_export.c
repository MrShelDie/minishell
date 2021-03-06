/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 22:58:22 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 18:51:05 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	putstr(int len, char **map_buff, char **value)
{
	int		i;

	i = -1;
	while (++i < len - 1)
	{
		if (ft_strcmp(value[i], "") == 0)
			printf("declare -x %s\n", map_buff[i]);
		else
			printf("declare -x %s=\"%s\"\n", map_buff[i], value[i]);
	}
}

int	print_sort_env(t_map *map)
{
	char	**map_buff;
	char	**value;
	int		err;

	err = 0;
	value = NULL;
	map_buff = NULL;
	map_buff = create_buff(map_buff, map, &err);
	value = create_valbuf(value, map, &err);
	if (err == 1)
	{
		delete_buff(map_buff, value, map->length);
		return (FAIL);
	}
	map_buff = sort_buff(map_buff, map->length, &value);
	putstr((int)map->length, map_buff, value);
	delete_buff(map_buff, value, map->length);
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
		if (map_add(data->env_map, cmd->data[i], "") == FAIL)
			return (FAIL);
		if (vector_add(data->env_vector, "") == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	tmp = ft_split(cmd->data[i], '=');
	if (!tmp)
		return (FAIL);
	if (map_add(data->env_map, tmp[0], tmp[1]) == FAIL)
		return (FAIL);
	if (vector_add(data->env_vector, tmp[1]) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	ft_export(t_vector *cmd, t_shell_data *data)
{
	if (cmd->length < 2)
	{
		if (print_sort_env(data->env_map) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	if (add_data(data, cmd) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
