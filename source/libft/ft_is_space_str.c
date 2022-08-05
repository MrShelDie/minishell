/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_space_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:28:01 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/05 14:26:44 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the string consists of only whitespace characters.
 * 
 * @param str The string to be checked.
 * @return 1 if the string consists of only whitespace characters,
 * 		   0 if not.
 */
int	ft_is_space_str(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		++str;
	}
	return (1);
}
