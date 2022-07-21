/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:46:26 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/21 14:48:36 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strldup(const char *s1, size_t len)
{
	char	*res;

	if (!s1)
		return (NULL);
	++len;
	res = (char *)malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len);
	return (res);
}
