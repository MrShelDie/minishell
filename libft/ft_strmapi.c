/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:42:10 by gannemar          #+#    #+#             */
/*   Updated: 2021/10/15 19:42:11 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(
	char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	size_t			len;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
		result[i] = f(i, s[i]);
	result[len] = '\0';
	return (result);
}
