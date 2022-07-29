/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_substr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:19:42 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/29 15:24:03 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"
#include <stdlib.h>

int	append_substr(char **dst, const char *src, size_t len)
{
	char	*new_dst;
	char	*substr;

	substr = ft_substr(src, 0, len);
	if (!substr)
	{
		free(*dst);
		return (FAIL);
	}
	new_dst = ft_strjoin(*dst, substr);
	free(*dst);
	free(substr);
	*dst = new_dst;
	if (!new_dst)
		return (FAIL);
	return (SUCCESS);
}
