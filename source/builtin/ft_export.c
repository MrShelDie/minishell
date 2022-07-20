/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 22:58:22 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 17:40:19 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/builtins.h"
#include "../../include/minishell.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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

int	add_data(t_shell_data *data, t_cmd *cmd)
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

int	ft_export(t_cmd *cmd, t_shell_data *data)
{
	if (cmd->len < 2)
	{
		if (print_sort_env(data->env_map) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	if (add_data(data, cmd) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
