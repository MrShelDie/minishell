/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:27:03 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/03 13:16:31 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "lexer.h"

/**
 * @brief Frees up the token's memory.
 * 
 * @param token Pointer to the token.
 */
void	destroy_token(void *token)
{
	if (!token)
		return ;
	free(((t_token *)token)->value);
	free(token);
}

void	move_to_closed_quote(const char **str)
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
		ft_putstr_fd("'newline'\n", 2);
		return (FAIL);
	}
	return (SUCCESS);
}
