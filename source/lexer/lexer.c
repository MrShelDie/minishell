/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:26:28 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 14:25:09 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "shell_error.h"

/**
 * @brief Checks if the next few characters are metacharacters.
 * 
 * @param Pointer to the first character.
 * @return 0 if the characters are not metacharacters or if a NULL pointer
 * 		is passed to the function. Otherwise returns 1.
 */
static int	is_metacharacter(const char *c)
{
	if (!c)
		return (0);
	if (*c == '\0' || *c == '|' || *c == '('
		|| *c == ')' || *c == '<' || *c == '>'
		|| ft_strncmp(c, "&&", 2) == 0
	)
		return (1);
	return (0);
}

/**
 * @brief Gets the length of a WORD type token, including text in quotes.
 * 
 * @param str Pointer to the first token symbol.
 * @return Token length.
 */
static size_t	get_word_token_length(const char *str)
{
	const char	*str_start;

	if (!str)
		return (0);
	str_start = str;
	while (!ft_isspace(*str) && !is_metacharacter(str))
	{
		if (*str == '\'' || *str == '\"')
			move_to_closed_quote(&str);
		++str;
	}
	return (str - str_start);
}

/**
 * @brief Creates a new token.
 * 		Moves the pointer to the current character
 * 		by a value equal to the length of the read token.
 * 
 * @param str Double pointer to the current character.
 * @param id ID to be assigned to the token.
 * @param value_length Token length.
 * @return A pointer to the created token structure.
 * 		   In case of a memory allocation error, returns NULL.
 */
static t_token_list	*get_token(
	const char **current_char, t_token_id id, size_t value_length)
{
	t_token_list	*token_list_node;
	t_token			*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		print_error(strerror(errno));
		return (NULL);
	}
	token->id = id;
	token->value = ft_substr(*current_char, 0, value_length);
	if (!token->value)
	{
		print_error(strerror(errno));
		destroy_token(token);
		return (NULL);
	}
	token_list_node = ft_lstnew(token);
	if (!token_list_node)
	{
		print_error(strerror(errno));
		destroy_token(token);
	}
	*current_char += value_length;
	return (token_list_node);
}

/**
 * @brief Gets the next token, moves the pointer to the current character
 * 		by a value equal to the length of the read token.
 * 
 * @param current_char Double pointer to the current character
 * @return Pointer to the created token.
 *		   In case of a memory allocation error, returns NULL.
 */
static t_token_list	*get_next_token(const char **current_char)
{
	while (ft_isspace(**current_char))
		++(*current_char);
	if (ft_strncmp(*current_char, "<<", 2) == 0)
		return (get_token(current_char, TOKEN_D_ANG_BR_L, 2));
	else if (ft_strncmp(*current_char, ">>", 2) == 0)
		return (get_token(current_char, TOKEN_D_ANG_BR_R, 2));
	else if (ft_strncmp(*current_char, "&&", 2) == 0)
		return (get_token(current_char, TOKEN_AND, 2));
	else if (ft_strncmp(*current_char, "||", 2) == 0)
		return (get_token(current_char, TOKEN_OR, 2));
	else if (**current_char == '\0')
		return (get_token(current_char, TOKEN_NEW_LINE, 1));
	else if (**current_char == '|')
		return (get_token(current_char, TOKEN_PIPE, 1));
	else if (**current_char == '(')
		return (get_token(current_char, TOKEN_PAR_L, 1));
	else if (**current_char == ')')
		return (get_token(current_char, TOKEN_PAR_R, 1));
	else if (**current_char == '<')
		return (get_token(current_char, TOKEN_ANG_BR_L, 1));
	else if (**current_char == '>')
		return (get_token(current_char, TOKEN_ANG_BR_R, 1));
	else
		return (get_token(current_char, TOKEN_WORD,
				get_word_token_length(*current_char)));
}

/**
 * @brief Splits a string into tokens.
 * 
 * @param str User input string.
 * @return List of tokens.
 * 		   In case of a memory allocation error or passing
 * 		   a null pointer to an argument, returns NULL.
 */
t_token_list	*get_token_list(const char *str)
{
	t_token_list	*token_list;
	t_token_list	*new_token;
	const char		*current_char;

	if (!str)
		return (NULL);
	current_char = str;
	token_list = NULL;
	while (!token_list
		|| ((t_token *)(new_token->content))->id != TOKEN_NEW_LINE)
	{
		new_token = get_next_token(&current_char);
		if (!new_token)
		{
			ft_lstclear(&token_list, destroy_token);
			return (NULL);
		}
		ft_lstadd_back(&token_list, new_token);
	}
	return (token_list);
}
