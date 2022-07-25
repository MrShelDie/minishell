/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:56:57 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/25 16:57:12 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_private.h"

bool	check_expansion(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"' || (*str == '$' && *(str + 1)))
			return (true);
	}
	return (false);
}
