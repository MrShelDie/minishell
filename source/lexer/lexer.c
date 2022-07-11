/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:26:28 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/11 19:18:26 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_private.h"
#include <stdlib.h>

/**
 * @brief Creates a new token. Increases the offset index by value_length.
 * 
 * @param str A string whose value_length characters, starting from
 * 			  the offset index, will be written to the value field in t_token.
 * @param offset The offset index. Will be increased by value_length.
 * @param id Token's ID
 * @param value_length Token length
 * @return A pointer to the created token structure.
 * 		   In case of a memory allocation error, returns NULL.
 */
static t_list	*get_token(
	const char *str, size_t *offset, t_token_id id, size_t value_length)
{
	t_list	*list_node;
	t_token	*token;
	char	*value;

	value = (char *)malloc(sizeof(char) * (value_length + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, str, value_length + 1);
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
	(*offset) += value_length;
	return (list_node);
}

/**
 * @brief Gets the length of a WORD type token, including quotes.
 * 
 * @param str Pointer to the first token symbol.
 * @return Token length.
 */
static size_t	get_token_length(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (!ft_isspace(str[i]) && ft_strncmp(str + i, "&&", 2) != 0)
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				;
		}
		else if (str[i] == '\"')
		{
			while (str[++i] != '\'')
				;
		}
		++i;
	}
	return (i);
}

// static t_list	*get_next_subshell_token(const char *str, size_t *offset)
// {
// 	if (str[*offset] == '(')
// 		return (get_token(str, offset, PAR_L, 1));
// 	if (str[*offset] == ')')
// 		return (get_token(str, offset, PAR_R, 1));
// }

static t_list	*get_subshell_token_list(const char *str, size_t *offset)
{
	t_list	*subshell_list;
	t_list	*new_token;

	subshell_list = NULL;
	new_token = get_token(str, offset, ANG_BR_L, 1);
	if (!new_token)
		return (NULL);
	while (((t_token *)new_token)->id != END && ((t_token *)new_token)->id != PAR_R)
	{
		ft_lstadd_back(&subshell_list, new_token);
		if (str[*offset] == '(')
			new_token = get_subshell_token_list(str, offset));
		else if (str[*offset] == ')')
			new_token = get_token(str, offset));
	}
	
}

/**
 * @brief Gets the next sublist of tokens, moves the offset index.
 * 
 * @param str User Input string.
 * @param offset Offset index.
 * @return Pointer to the first node of the sublist.
 *		   In case of a memory allocation error, returns NULL.
 */
static t_list	*get_next_token_sublist(const char *str, size_t	*offset)
{
	while (ft_isspace(str[*offset]))
		++(*offset);	
	if (str[*offset] == '(')
		return (get_subshell_token_list(str, offset));
	else if (str[*offset] == '\0')
		return (get_token(str, offset, END, 1));
	else if (str[*offset] == '|')
		return (get_token(str, offset, PIPE, 1));
	else if (str[*offset] == '=')
		return (get_token(str, offset, EQUAL, 1));
	else if (str[*offset] == '<')
		return (get_token(str, offset, ANG_BR_L, 1));
	else if (str[*offset] == '>')
		return (get_token(str, offset, ANG_BR_R, 1));
	else if (ft_strncmp(str + *offset, "<<", 2))
		return (get_token(str, offset, D_ANG_BR_L, 2));
	else if (ft_strncmp(str + *offset, ">>", 2))
		return (get_token(str, offset, D_ANG_BR_R, 2));
	else if (ft_strncmp(str + *offset, "&&", 2))
		return (get_token(str, offset, AND, 2));
	else if (ft_strncmp(str + *offset, "||", 2))
		return (get_token(str, offset, OR, 2));
	else
		return (get_token(str, offset, WORD, get_token_length(str)));
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
	t_list	*new_token_sublist;
	size_t	offset;

	if (!str)
		return (NULL);
	offset = 0;
	token_list = NULL;
	new_token_sublist = get_next_token_sublist(str, &offset);
	if (!new_token_sublist)
	{
		ft_lstclear(&token_list, free_token);
		return (NULL);
	}
	while (((t_token *)(new_token_sublist->content))->id != END)
	{
		ft_lstadd_back(&token_list, new_token_sublist);
		new_token_sublist = get_next_token_sublist(str, &offset);
		if (!new_token_sublist)
		{
			ft_lstclear(&token_list, free_token);
			return (NULL);
		}
	}
	return (token_list);
}
