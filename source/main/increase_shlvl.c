/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase_shlvl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:44:07 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/05 14:57:11 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell_private.h"
#include "libft.h"

static int	add_new_shlvl_to_map(t_map *map)
{
	return (map_add(map, "SHLVL", "1"));
}

static int	add_increased_shlvl_to_map(t_map *map, const char *shlvl_str)
{
	int		shlvl_num;
	int		add_status;
	char	*new_shlvl_str;

	shlvl_num = ft_atoi(shlvl_str);
	new_shlvl_str = ft_itoa(++shlvl_num);
	if (!new_shlvl_str)
		return (FAIL);
	add_status = map_add(map, "SHLVL", new_shlvl_str);
	free(new_shlvl_str);
	return (add_status);
}

/* map_get is not protected because the SHLVL is already in map. */
static int	copy_shlvl_from_map_to_vector(t_map *map, t_vector *vector)
{
	const char	*shlvl_value;

	shlvl_value = map_get(map, "SHLVL");
	return (replace_string_in_vector_by_key(vector, "SHLVL", shlvl_value));
}

static int	increase_shlvl_in_map(t_map *map)
{
	const char	*shlvl_str;
	int			add_status;

	shlvl_str = map_get(map, "SHLVL");
	if (!shlvl_str)
		add_status = add_new_shlvl_to_map(map);
	else
		add_status = add_increased_shlvl_to_map(map, shlvl_str);
	return (add_status);
}

int	increase_shlvl_in_map_and_vector(t_map *map, t_vector *vector)
{
	if (increase_shlvl_in_map(map) == FAIL
		|| copy_shlvl_from_map_to_vector(map, vector) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
