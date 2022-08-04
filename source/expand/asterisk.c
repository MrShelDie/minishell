/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:02:19 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 14:30:24 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "expand_private.h"
#include "shell_error.h"

static size_t	get_asterisk_count(const char *str)
{
	size_t	asterisk_count;

	asterisk_count = 0;
	while (*str)
	{
		if (*str == '*')
			++asterisk_count;
		++str;
	}
	return (asterisk_count);
}

static int	init_asterisk_map(t_asterisk *asterisk_map, const char *str)
{
	ft_bzero(asterisk_map, sizeof(t_asterisk));
	asterisk_map->size = get_asterisk_count(str);
	if (asterisk_map->size == 0)
		return (SUCCESS);
	asterisk_map->array = ft_calloc(asterisk_map->size, sizeof(bool));
	if (!asterisk_map->array)
	{
		print_error(strerror(errno));
		return (FAIL);
	}
	return (SUCCESS);
}

void	free_asterisk_map(t_asterisk *asterisk_map)
{
	free(asterisk_map->array);
	ft_bzero(asterisk_map, sizeof(t_asterisk));
}

int	fill_asterisk_map(t_asterisk *asterisk_map, const char *str)
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
