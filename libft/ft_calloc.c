/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:50:50 by gannemar          #+#    #+#             */
/*   Updated: 2021/10/15 19:40:30 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	allsize;

	allsize = nmemb * size;
	ptr = malloc(allsize);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, allsize);
	return (ptr);
}
