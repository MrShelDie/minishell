/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:16:38 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/12 17:20:18 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_private.h"
#include <stdlib.h>

/**
 * @brief Gets the length of a WORD type token, including text in quotes.
 * 
 * @param str Pointer to the first token symbol.
 * @return Token length.
 */
size_t	get_word_token_length(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (!ft_isspace(str[i]) && !is_special(str[i])
		&& ft_strncmp(str + i, "&&", 2) != 0)
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
t_list	*get_token(
	const char **pp_current_char, t_token_id id, size_t value_length)
{
	t_list	*list_node;
	t_token	*token;
	char	*value;

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
