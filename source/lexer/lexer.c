/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:26:28 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/10 15:25:41 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

static void	skip_spaces(const char *str, size_t	*offset)
{
	while (str[*offset] == ' ' || str[*offset] == '\t'
		|| str[*offset] == '\n' || str[*offset] == '\v'
		|| str[*offset] == '\f' || str[*offset] == '\r')
			++(*offset);
}

/**
 * @brief Gets the next token, moves the offset index.
 * 
 * @param str User Input string.
 * @param offset Offset index.
 * @return The node of the token list.
 *		   In case of a memory allocation error, returns NULL.
 */
t_list	*get_next_token(const char *str, size_t	*offset)
{
	skip_spaces(str, offset);
	if (str[*offset] == '\0')
	{
		// TODO return NEWLINE token
	}
	else if (str[*offset] == '|')
	{
		// TODO return PIPE token
	}
	else if (str[*offset] == '(')
	{
		// TODO return PAR_L token
	}
	else if (str[*offset] == ')')
	{
		// TODO return PAR_R token
	}
	else if (str[*offset] == '<')
	{
		// TODO return ANGL_BR_L token
	}
	else if (str[*offset] == '>')
	{
		// TODO return ANGL_BR_R token
	}
	// else if (str[*offset] == '<<')
	// {
	// 	// TODO return D_ANGL_BR_L token
	// }
	// else if (str[*offset] == '>>')
	// {
	// 	// TODO return D_ANGL_BR_R token
	// }
}

/**
 * @brief Splits a string into tokens.
 * 
 * @param str User input string.
 * @return List of tokens.
 * 		   In case of a memory allocation error or passing
 * 		   a null pointer to an argument, returns NULL.
 */
t_list	*get_token_list(const char *str)
{
	t_list	*token_list;
	t_list	*new_token;
	size_t	offset;

	if (!str)
		return (NULL);
	offset = 0;
	token_list = NULL;
	new_token = get_next_token(str, &offset);
	if (!new_token)
	{
		ft_lstclear(&token_list, free);
		return (NULL);
	}
	while (((t_token *)(new_token->content))->id != NEWLINE)
	{
		ft_lstadd_back(&token_list, new_token);
		new_token = get_next_token(str, &offset);
		if (!new_token)
		{
			ft_lstclear(&token_list, free);
			return (NULL);
		}
	}
	return (token_list);
}
