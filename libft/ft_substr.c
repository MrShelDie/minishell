/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:42:31 by gannemar          #+#    #+#             */
/*   Updated: 2021/10/15 19:42:32 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_get_substr_len(
	char const **s, unsigned int start, size_t max_len)
{
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(*s);
	if (start >= s_len)
		return (0);
	*s += start;
	i = 0;
	while ((*s)[i] && i < max_len)
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	substr_len;
	char	*substr;

	if (!s)
		return (NULL);
	substr_len = ft_get_substr_len(&s, start, len) + 1;
	substr = (char *)malloc(sizeof(char) * substr_len);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s, substr_len);
	return (substr);
}
