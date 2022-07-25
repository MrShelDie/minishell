/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_with_expanded_str.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:54:24 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/25 16:54:48 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_private.h"
#include <stdlib.h>

int	replace_with_expanded_str(
	const t_map *env_map, const char **str)
{
	char	*expanded;

	expanded = ft_strdup("");
	if (!expanded)
		return (FAIL);
	while (*str)
	{
		if (!append_regular_str(&expanded, str)
			|| !append_expanded_str(env_map, &expanded, str)
		)
			return (FAIL);
	}
	free(*str);
	*str = expanded;
	return (SUCCESS);
}
