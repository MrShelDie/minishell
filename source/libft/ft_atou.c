/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 16:02:54 by medric            #+#    #+#             */
/*   Updated: 2022/08/06 13:17:03 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_skip_spaces(const char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\n'
		|| **str == '\v' || **str == '\f' || **str == '\r')
		(*str)++;
}

static long int	ft_str_to_num(const char **str, int *ndigit)
{
	long int	num;

	num = 0;
	while (ft_isdigit(**str))
	{
		num = num * 10 + (**str - '0');
		(*ndigit)++;
		(*str)++;
	}
	return (num);
}

unsigned int	ft_atou(const char *str)
{
	int			ndigit;
	long int	num;

	num = 0;
	ndigit = 0;
	ft_skip_spaces(&str);
	num = ft_str_to_num(&str, &ndigit);
	if (ndigit > 19)
		return (-1);
	return ((unsigned int)num);
}
