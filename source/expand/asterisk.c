/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:02:19 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/25 17:10:24 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_private.h"
#include "libft.h"
#include <stdlib.h>

static size_t	get_asterisk_count(const char *str)
{
	size_t	asterisk_count;
	
	asterisk_count = 0;
	while (*str)
	{
		if (*str == '*')
			++asterisk_count;
	}
	return (asterisk_count);
}

static int	init_asterisk_map(t_asterisk_map *asterisk_map, const char *str)
{
	ft_bzero(asterisk_map, sizeof(t_asterisk_map));
	asterisk_map->size = get_asterisk_count(str);
	if (asterisk_map->size == 0)
		return (SUCCESS);
	asterisk_map->array = (bool *)malloc(sizeof(bool) * asterisk_map->size);
	if (!asterisk_map->array)
		return (FAIL);
	ft_bzero(asterisk_map->array, sizeof(bool) * asterisk_map->size);
	return (SUCCESS);
}

void	free_asterisk_map(t_asterisk_map *asterisk_map)
{
	if (asterisk_map->array)
		free(asterisk_map->array);
	ft_bzero(asterisk_map, sizeof(t_asterisk_map));
}

int	fill_asterisk_map(t_asterisk_map *asterisk_map, const char *str)
{
	t_quote			quote;
	size_t			asterisk_idx;
	
	if (!init_asterisk_map(asterisk_map, str))
		return (FAIL);
	ft_bzero(&quote, sizeof(t_quote));
	asterisk_idx = 0;
	while (*str)
	{
		if (quote.inside && *str == quote.symbol)
			quote.inside = false;
		else if (!quote.inside && (*str == '\'' || *str == '\"'))
		{
			quote.inside = true;
			quote.symbol = *str;
		}
		else if (*str == '*')
		{
			asterisk_map->array[asterisk_idx++] = !quote.inside;
			if (!quote.inside)
				asterisk_map->contains_wildcard = true;	
		}
		++str;
	}
	return (SUCCESS);
}
