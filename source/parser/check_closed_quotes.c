/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:31:35 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/02 16:33:28 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"

static void	move_to_closed_quote(const char **str)
{
	char	closed_quote;

	closed_quote = **str;
	++(*str);
	while (**str && **str != closed_quote)
		++(*str);
}

static bool	is_quote_closed(const char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			move_to_closed_quote(&str);
		if (!*str)
			return (false);
		++str;
	}
	return (true);
}

int	check_closed_quotes(const char *str)
{
	if (!is_quote_closed(str))
	{
		ft_putstr_fd(SYNTAX_ERR_MSG, 2);
		ft_putstr_fd("'newline\n'", 2);
		return (FAIL);
	}
	return (SUCCESS);
}
