/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_group.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:39:52 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/19 20:41:25 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include <stddef.h>

void	destroy_pipe_group(void *pipe_group)
{
	ft_lstclear((t_list **)&pipe_group, destroy_cmd);
}

static t_cmd_list	*get_next_cmd_list_node(t_token_list **token)
{
	t_cmd		*cmd;
	t_cmd_list	*cmd_list_node;

	cmd = get_next_cmd(token);
	if (!cmd)
		return (NULL);
	cmd_list_node = ft_lstnew(cmd);
	if (!cmd_list_node)
	{
		destroy_cmd(cmd);
		return (NULL);
	}
	return (cmd_list_node);
}

static t_cmd_list	*get_next_cmd_list(t_token_list **token)
{
	t_cmd_list	*cmd_list;
	t_cmd_list	*cmd_list_node;

	cmd_list = NULL;
	while (((t_token *)((*token)->content))->id != TOKEN_NEW_LINE
		&& ((t_token *)((*token)->content))->id != TOKEN_AND
		&& ((t_token *)((*token)->content))->id != TOKEN_OR)
	{
		cmd_list_node = get_next_cmd_list_node(token);
		if (!cmd_list_node)
		{
			ft_lstclear(&cmd_list, destroy_cmd);
			return (NULL);
		}
		ft_lstadd_back(&cmd_list, cmd_list_node);
		if (((t_token *)((*token)->content))->id == TOKEN_PIPE
			&& ((t_token *)((*token)->next->content))->id == TOKEN_NEW_LINE)
		{
			write_unexpected_token_error(((t_token *)((*token)->next->content))->id);
	 		return (NULL);
		}
		if (((t_token *)((*token)->content))->id == TOKEN_PIPE)
			*token = (*token)->next;
	}
	return (cmd_list);
}

t_pipe_group_list	*get_next_pipe_group(t_token_list **token)
{
	t_pipe_group_list	*pipe_group_list_node;
	t_cmd_list			*cmd_list;
	t_token_id			token_id;

	if (!token || !*token)
		return (NULL);
	token_id = ((t_token *)((*token)->content))->id;
	if (token_id == TOKEN_AND || token_id == TOKEN_OR
		|| token_id == TOKEN_NEW_LINE)
	{
		write_unexpected_token_error(token_id);
		return (NULL);
	}
	cmd_list = get_next_cmd_list(token);
	if (!cmd_list)
		return (NULL);
	pipe_group_list_node = ft_lstnew(cmd_list);
	if (!pipe_group_list_node)
		ft_lstclear(&cmd_list, destroy_cmd);
	return (pipe_group_list_node);
}
