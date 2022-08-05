/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 16:02:54 by medric            #+#    #+#             */
/*   Updated: 2022/08/05 16:04:31 by medric           ###   ########.fr       */
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

unsigned int	ft_atou(const char *str)
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
		return (-1);
	return ((unsigned int)num);
}
