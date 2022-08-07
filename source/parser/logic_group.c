/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_group.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:39:52 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/07 17:57:09 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <string.h>

#include "parser_private.h"
#include "shell_error.h"

void	destroy_cmd_list(void *cmd_list)
{
	ft_lstclear((t_list **)&cmd_list, destroy_cmd);
}

static t_cmd_list	*get_next_cmd_list_node(
	t_token_list **token, size_t *recursion_level)
{
	t_cmd		*cmd;
	t_cmd_list	*cmd_list_node;

	cmd = get_next_cmd(token, recursion_level);
	if (!cmd)
		return (NULL);
	cmd_list_node = ft_lstnew(cmd);
	if (!cmd_list_node)
	{
		print_error(strerror(errno));
		destroy_cmd(cmd);
		return (NULL);
	}
	return (cmd_list_node);
}

static int	append_next_cmd_list_node(t_cmd_list **cmd_list,
	t_token_list **token_list_node, size_t *recursion_level)
{
	t_cmd_list	*cmd_list_node;
	t_token_id	current_token_id;
	t_token_id	next_token_id;

	cmd_list_node = get_next_cmd_list_node(token_list_node, recursion_level);
	if (!cmd_list_node)
	{
		ft_lstclear(cmd_list, destroy_cmd);
		return (FAIL);
	}
	ft_lstadd_back(cmd_list, cmd_list_node);
	current_token_id = ((t_token *)((*token_list_node)->content))->id;
	if (current_token_id != TOKEN_PIPE)
		return (SUCCESS);
	next_token_id = ((t_token *)((*token_list_node)->next->content))->id;
	if (next_token_id == TOKEN_NEW_LINE)
	{
		unexpected_token_error((*token_list_node)->next->content,
			*recursion_level);
		return (FAIL);
	}
	return (SUCCESS);
}

static t_cmd_list	*get_next_cmd_list(
	t_token_list **token_list_node, size_t *recursion_level)
{
	t_cmd_list	*cmd_list;

	if (((t_token *)((*token_list_node)->content))->id == TOKEN_PIPE)
	{
		unexpected_token_error((*token_list_node)->content, *recursion_level);
		return (NULL);
	}
	cmd_list = NULL;
	while (((t_token *)((*token_list_node)->content))->id != TOKEN_NEW_LINE
		&& ((t_token *)((*token_list_node)->content))->id != TOKEN_AND
		&& ((t_token *)((*token_list_node)->content))->id != TOKEN_OR)
	{
		if (!append_next_cmd_list_node(
				&cmd_list, token_list_node, recursion_level))
			return (NULL);
		if (((t_token *)((*token_list_node)->content))->id == TOKEN_PIPE)
			*token_list_node = (*token_list_node)->next;
	}
	return (cmd_list);
}

t_logic_group_list	*get_next_logic_group_list_node(
	t_token_list **token_list_node, size_t *recursion_level)
{
	t_logic_group_list	*logic_group_list_node;
	t_cmd_list			*cmd_list;
	t_token_id			token_id;

	if (!token_list_node || !*token_list_node)
		return (NULL);
	token_id = ((t_token *)((*token_list_node)->content))->id;
	if (token_id == TOKEN_AND || token_id == TOKEN_OR
		|| token_id == TOKEN_NEW_LINE)
	{
		unexpected_token_error((*token_list_node)->content, *recursion_level);
		return (NULL);
	}
	cmd_list = get_next_cmd_list(token_list_node, recursion_level);
	if (!cmd_list)
		return (NULL);
	logic_group_list_node = ft_lstnew(cmd_list);
	if (!logic_group_list_node)
	{
		print_error(strerror(errno));
		ft_lstclear(&cmd_list, destroy_cmd);
	}
	return (logic_group_list_node);
}
