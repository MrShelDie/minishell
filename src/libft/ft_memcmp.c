/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:51:09 by gannemar          #+#    #+#             */
/*   Updated: 2021/10/15 19:41:01 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*s1c;
	char	*s2c;

	i = 0;
	s1c = (char *)s1;
	s2c = (char *)s2;
	while (i < n)
	{
		if (s1c[i] != s2c[i])
			return ((unsigned char)s1c[i] - (unsigned char)s2c[i]);
		i++;
	}
	return (0);
}
