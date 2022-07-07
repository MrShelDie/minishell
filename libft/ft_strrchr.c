/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:51:43 by gannemar          #+#    #+#             */
/*   Updated: 2021/11/15 14:47:28 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			last = s;
		s++;
	}
	if ((unsigned char)*s == (unsigned char)c)
		last = s;
	return ((char *)last);
}
