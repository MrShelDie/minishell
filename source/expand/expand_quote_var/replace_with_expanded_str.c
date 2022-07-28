/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_with_expanded_str.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:54:24 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/28 20:42:41 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"
#include <stdlib.h>

int	replace_with_expanded_str(
	const t_map *env_map, void **str)
{
	char	**_str;
	char	*str_start;
	char	*expanded;

	_str = (char **)str;
	str_start = *_str;
	expanded = ft_strdup("");
	if (!expanded)
		return (FAIL);
	while (**_str)
	{
		if (!append_regular_str(&expanded, _str))
			return (FAIL);
		if (!**_str)
			break ;
		if (!append_expanded_str(env_map, &expanded, _str))
			return (FAIL);
	}
	free(str_start);
	*str = expanded;
	return (SUCCESS);
}
