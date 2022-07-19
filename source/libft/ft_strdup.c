/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:18:47 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/19 14:43:17 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*res;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	res = (char *)malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len);
	return (res);
}
