/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_ut.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:28:17 by medric            #+#    #+#             */
/*   Updated: 2022/08/02 18:55:46 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"
#include <stdlib.h>

char	**create_buff(char **map_buff, t_vector *map, int *err)
{
	int			i;

	i = 0;
	map_buff = (char **)malloc(sizeof(char *) * (map->length));
	if (!map_buff)
		*err = 1;
	while (i < (int)map->length)
	{
		map_buff[i] = (char *)malloc(sizeof(char) * (ft_strlen(map->data[i]) + 1));
		if (!map_buff[i])
			*err = 1;
		ft_strcpy(map_buff[i], map->data[i], (ft_strlen(map->data[i]) + 1));
		i++;
	}
	return (map_buff);
}

char	**create_valbuf(char **value, t_map *map, int *err)
{
	int			i;
	t_map_node	*nt;

	i = 0;
	nt = map->head;
	value = (char **)malloc(sizeof(char *) * (map->length));
	if (!value)
		*err = 1;
	while (i < (int)map->length)
	{
		value[i] = (char *)malloc(sizeof(char) * \
			(ft_strlen(map_get(map, nt->key)) + 1));
		if (!value[i])
			*err = 1;
		ft_strcpy(value[i], map_get(map, nt->key), \
			(ft_strlen(map_get(map, nt->key)) + 1));
		nt = nt->next;
		i++;
	}
	return (value);
}

char	**sort_buff(char **buff, int len)
{
	char		*tmp;
	int			i;
	int			j;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(buff[j], buff[j + 1]) > 0)
			{
				tmp = buff[j];
				buff[j] = buff[j + 1];
				buff[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (buff);
}

void	delete_buff(char **m, int length)
{
	int	i;

	i = -1;
	if (m != NULL)
	{
		while (++i < length - 1)
			free(m[i]);
	}
}

int	ft_searchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
