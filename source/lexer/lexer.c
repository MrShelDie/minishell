/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:26:28 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/13 16:15:38 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_private.h"

/**
 * @brief Gets a token that is outside the parentheses.
 * 		All tokens outside the parentheses and the parentheses themselves receive
 * 		an identifier according to their value.
 * 		Moves the pointer to the current character
 * 		by a value equal to the length of the read token.
 * 
 * @param current_char Double pointer to the current character.
 * @return Pointer to the created token.
 *		   In case of a memory allocation error, returns NULL.
 */
static t_list	*get_token_outside_parenthesis(const char **pp_current_char)
{
	if (ft_strncmp(*pp_current_char, "<<", 2) == 0)
		return (get_token(pp_current_char, D_ANG_BR_L, 2));
	else if (ft_strncmp(*pp_current_char, ">>", 2) == 0)
		return (get_token(pp_current_char, D_ANG_BR_R, 2));
	else if (ft_strncmp(*pp_current_char, "&&", 2) == 0)
		return (get_token(pp_current_char, AND, 2));
	else if (ft_strncmp(*pp_current_char, "||", 2) == 0)
		return (get_token(pp_current_char, OR, 2));
	else if (**pp_current_char == '|')
		return (get_token(pp_current_char, PIPE, 1));
	else if (**pp_current_char == '(')
		return (get_token(pp_current_char, PAR_L, 1));
	else if (**pp_current_char == ')')
		return (get_token(pp_current_char, PAR_R, 1));
	else if (**pp_current_char == '<')
		return (get_token(pp_current_char, ANG_BR_L, 1));
	else if (**pp_current_char == '>')
		return (get_token(pp_current_char, ANG_BR_R, 1));
	else
		return (get_token(pp_current_char, WORD,
				get_word_token_length(*pp_current_char)));
}

/**
 * @brief Gets a token that is inside the parentheses. All tokens inside the
 * 		parentheses, with the exception of the parentheses themselves,
 * 		will be given a WORD ID.
 * 		Moves the pointer to the current character
 * 		by a value equal to the length of the read token.
 * 
 * @param pp_current_char Double pointer to the current character.
 * @return Pointer to the created token.
 *		   In case of a memory allocation error, returns NULL.
 */
static t_list	*get_token_inside_parenthesis(const char **pp_current_char)
{
	if (**pp_current_char == '|' || **pp_current_char == '('
		|| **pp_current_char == ')' || **pp_current_char == '<'
		|| **pp_current_char == '>'
	)
		return (get_token(pp_current_char, WORD, 1));
	if (ft_strncmp(*pp_current_char, "<<", 2) == 0
		|| ft_strncmp(*pp_current_char, ">>", 2) == 0
		|| ft_strncmp(*pp_current_char, "&&", 2) == 0
		|| ft_strncmp(*pp_current_char, "||", 2) == 0
	)
		return (get_token(pp_current_char, WORD, 2));
	return (get_token(pp_current_char, WORD,
			get_word_token_length(*pp_current_char)));
}

/**
 * @brief Gets the next token, moves the pointer to the current character
 * 		by a value equal to the length of the read token.
 * 
 * @param pp_current_char Double pointer to the current character
 * @return Pointer to the created token.
 *		   In case of a memory allocation error, returns NULL.
 */
static t_list	*get_next_token(const char **pp_current_char)
{
	static size_t	open_parenthesis_counter;
	t_list			*result;
	char			current_char;

	while (ft_isspace(**pp_current_char))
		++(*pp_current_char);
	if (**pp_current_char == '\0')
	{
		open_parenthesis_counter = 0;
		return (get_token(pp_current_char, END, 1));
	}
	current_char = **pp_current_char;
	if (current_char == ')' && open_parenthesis_counter > 0)
		--open_parenthesis_counter;
	if (open_parenthesis_counter > 0)
		result = get_token_inside_parenthesis(pp_current_char);
	else
		result = get_token_outside_parenthesis(pp_current_char);
	if (current_char == '(')
		++open_parenthesis_counter;
	return (result);
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
	t_list		*token_list;
	t_list		*new_token;
	const char	*p_current_char;

	if (!str)
		return (NULL);
	p_current_char = str;
	token_list = NULL;
	while (!token_list || ((t_token *)(new_token->content))->id != END)
	{
		new_token = get_next_token(&p_current_char);
		if (!new_token)
		{
			ft_lstclear(&token_list, free_token);
			return (NULL);
		}
		ft_lstadd_back(&token_list, new_token);
	}
	return (token_list);
}
