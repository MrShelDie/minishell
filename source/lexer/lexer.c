/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:26:28 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/14 23:46:41 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

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
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (!ft_isspace(str[i]) && !is_metacharacter(str + i))
	{
		if (str[i] == '\'')
		{
			++i;
			while (str[i] != '\'' && str[i] != '\0')
				++i;
		}
		else if (str[i] == '\"')
		{
			++i;
			while (str[i] != '\"' && str[i] != '\0')
				++i;
		}
		++i;
	}
	return (i);
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
	const char **pp_current_char, t_token_id id, size_t value_length)
{
	t_token_list	*list_node;
	t_token			*token;
	char			*value;

	value = (char *)malloc(sizeof(char) * (value_length + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, *pp_current_char, value_length + 1);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		free(value);
		return (NULL);
	}
	token->id = id;
	token->value = value;
	list_node = ft_lstnew(token);
	if (!list_node)
	{
		free(value);
		free(token);
	}
	*pp_current_char += value_length;
	return (list_node);
}

/**
 * @brief Gets the next token, moves the pointer to the current character
 * 		by a value equal to the length of the read token.
 * 
 * @param pp_current_char Double pointer to the current character
 * @return Pointer to the created token.
 *		   In case of a memory allocation error, returns NULL.
 */
static t_token_list	*get_next_token(const char **pp_current_char)
{
	while (ft_isspace(**pp_current_char))
		++(*pp_current_char);
	if (ft_strncmp(*pp_current_char, "<<", 2) == 0)
		return (get_token(pp_current_char, D_ANG_BR_L, 2));
	else if (ft_strncmp(*pp_current_char, ">>", 2) == 0)
		return (get_token(pp_current_char, D_ANG_BR_R, 2));
	else if (ft_strncmp(*pp_current_char, "&&", 2) == 0)
		return (get_token(pp_current_char, AND, 2));
	else if (ft_strncmp(*pp_current_char, "||", 2) == 0)
		return (get_token(pp_current_char, OR, 2));
	else if (**pp_current_char == '\0')
		return (get_token(pp_current_char, NEW_LINE, 1));
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
	const char		*p_current_char;

	if (!str)
		return (NULL);
	p_current_char = str;
	token_list = NULL;
	while (!token_list || ((t_token *)(new_token->content))->id != NEW_LINE)
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
