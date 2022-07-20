/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_subshell_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:33:11 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/20 17:34:43 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser_private.h"
#include "libft.h"
#include <stdlib.h>

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
		ft_lstclear(list, destroy_token);
		return (NULL);
	}
	new_node = ft_lstnew(new_token);
	if (!new_node)
	{
		destroy_token(new_token);
		ft_lstclear(list, destroy_token);
		return (NULL);
	}
	ft_lstadd_back(list, new_node);
	return (*list);
}
