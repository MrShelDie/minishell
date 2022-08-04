/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:56:57 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 15:58:26 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"
#include "libft.h"

static bool	is_variable_name_symbol(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

bool	is_variable(const char *str)
{
	return (str[0] == '$' && is_variable_name_symbol(str[1]));
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
