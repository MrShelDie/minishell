/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_regular_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:46:59 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/26 20:20:28 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_private.h"
#include <stdlib.h>

int	append_regular_str(char **dst, const char **src)
{
	size_t	i;
	char	*new_substr;
	
	i = 0;
	while ((*src)[i] && (*src)[i] != '\'' && (*src)[i] != '\"'
		&& !((*src)[i] == '$'
			&& (ft_isalnum((*src)[i + 1]) || (*src)[i + 1] == '_')))
		++i;
	new_substr = ft_strjoin(*dst, ft_strldup(*src, i));
	free(*dst);
	if (!new_substr)
		return (FAIL);
	*dst = new_substr;
	*src += i;
	return (SUCCESS);
}
