/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 12:48:20 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 12:51:48 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "../parser_private.h"
#include "shell_error.h"
#include "libft.h"

static t_redir	*create_redir(t_redir_id id, char *value)
{
	t_redir	*redir;
	char	*redir_value_copy;

	redir_value_copy = ft_strdup(value);
	if (!redir_value_copy)
	{
		print_error(strerror(errno));
		return (NULL);
	}
	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
	{
		print_error(strerror(errno));
		free(redir_value_copy);
		return (NULL);
	}
	redir->id = id;
	redir->value = redir_value_copy;
	return (redir);
}

void	destroy_redir(void *redir)
{
	free(((t_redir *)redir)->value);
}

int	fill_redir(t_cmd *cmd, t_token_list **token_list_node,
		t_redir_id redir_id, size_t *recursion_level)
{
	t_redir			*redir;
	t_redir_list	*redir_list_node;
	t_token			*token;

	*token_list_node = (*token_list_node)->next;
	token = (*token_list_node)->content;
	if (token->id != TOKEN_WORD)
	{
		unexpected_token_error(token, *recursion_level);
		return (FAIL);
	}
	redir = create_redir(redir_id, token->value);
	if (!redir)
		return (FAIL);
	redir_list_node = ft_lstnew(redir);
	if (!redir_list_node)
	{
		print_error(strerror(errno));
		destroy_redir(redir);
		return (FAIL);
	}
	ft_lstadd_back(&cmd->redir_list, redir_list_node);
	(*token_list_node) = (*token_list_node)->next;
	return (SUCCESS);
}
