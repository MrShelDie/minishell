/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:56:57 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/26 20:16:45 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_private.h"
#include "libft.h"

bool	check_expansion(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"'
			|| (*str == '$' && (ft_isalnum(str[1]) || str[1] == '_')))
			return (true);
		++str;
	}
	return (false);
}
