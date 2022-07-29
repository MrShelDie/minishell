/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_regular_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:46:59 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/29 15:26:39 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"
#include <stdlib.h>

int	append_regular_str(char **dst, char **src)
{
	size_t	i;
	
	i = 0;
	while ((*src)[i] && (*src)[i] != '\'' && (*src)[i] != '\"'
		&& !((*src)[i] == '$'
			&& (ft_isalnum((*src)[i + 1]) || (*src)[i + 1] == '_')))
		++i;
	if (!append_substr(dst, *src, i))
		return (FAIL);
	*src += i;
	return (SUCCESS);
}
