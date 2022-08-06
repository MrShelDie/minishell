/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:56:57 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/06 21:13:48 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"
#include "libft.h"

static bool	is_first_symbol_of_variable_name(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

bool	is_variable(const char *str)
{
	return (str[0] == '$' && is_first_symbol_of_variable_name(str[1]));
}

bool	check_expansion(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"' || is_variable(str))
			return (true);
		++str;
	}
	return (false);
}
