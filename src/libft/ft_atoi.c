/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:34:29 by gannemar          #+#    #+#             */
/*   Updated: 2021/10/15 19:40:28 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_skip_spaces(const char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\n'
		|| **str == '\v' || **str == '\f' || **str == '\r')
		(*str)++;
}

static	int	ft_get_sign(const char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (1);
	}
	if (**str == '+')
		(*str)++;
	return (0);
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

int	ft_atoi(const char *str)
{
	int			is_neg;
	int			ndigit;
	long int	num;

	num = 0;
	is_neg = 0;
	ndigit = 0;
	ft_skip_spaces(&str);
	is_neg = ft_get_sign(&str);
	num = ft_str_to_num(&str, &ndigit);
	if (ndigit > 19)
	{
		if (is_neg)
			return (0);
		return (-1);
	}
	if (is_neg)
		num *= -1;
	return ((int)num);
}
