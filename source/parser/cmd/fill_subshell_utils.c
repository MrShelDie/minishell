/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_subshell_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:33:11 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 13:12:28 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "../parser_private.h"
#include "shell_error.h"
#include "libft.h"

static t_token	*create_token(t_token_id id, char *value)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->id = id;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		print_error(strerror(errno));
		free(new_token);
		return (NULL);
	}
	return (new_token);
}

t_token_list	*append_new_token(
	t_token_list **list, t_token_id token_id, char *value)
{
	t_token_list	*new_node;
	t_token			*new_token;

	new_token = create_token(token_id, value);
	if (!new_token)
	{
		print_error(strerror(errno));
		ft_lstclear(list, destroy_token);
		return (NULL);
	}
	new_node = ft_lstnew(new_token);
	if (!new_node)
	{
		print_error(strerror(errno));
		destroy_token(new_token);
		ft_lstclear(list, destroy_token);
		return (NULL);
	}
	ft_lstadd_back(list, new_node);
	return (*list);
}

char	*str_append_word(char **dst, const char *src)
{
	char	*new_str;

	new_str = ft_strjoin(*dst, " ");
	if (!new_str)
	{
		print_error(strerror(errno));
		free(*dst);
		return (NULL);
	}
	free(*dst);
	*dst = new_str;
	new_str = ft_strjoin(new_str, src);
	if (!new_str)
	{
		print_error(strerror(errno));
		free(*dst);
		return (NULL);
	}
	free(*dst);
	*dst = new_str;
	return (*dst);
}
