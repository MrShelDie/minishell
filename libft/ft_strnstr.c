/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:35:00 by gannemar          #+#    #+#             */
/*   Updated: 2021/10/15 19:42:15 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	haystack_len;
	size_t	needle_len;
	size_t	i;

	haystack_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	if (haystack_len < needle_len || len < needle_len)
		return (NULL);
	i = 0;
	while (i < (haystack_len - needle_len + 1) && i < (len - needle_len + 1))
	{
		if (!ft_strncmp(haystack + i, needle, needle_len))
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
