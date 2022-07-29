/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 13:42:48 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/29 14:51:33 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	tolower(unsigned int pos, char *str)
{
	str[pos] = ft_tolower(str[pos]);
}

void	ft_strtolower(char *str)
{
	ft_striteri(str, tolower);
}
