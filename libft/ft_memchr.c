/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:51:05 by gannemar          #+#    #+#             */
/*   Updated: 2021/10/15 19:40:59 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*cs;

	cs = (char *)s;
	while (n > 0 && (unsigned char)*cs != (unsigned char)c)
	{
		cs++;
		n--;
	}
	if (n > 0)
		return ((void *)cs);
	return (NULL);
}
