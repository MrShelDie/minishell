/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:39:52 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/15 18:59:33 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include <stdlib.h>

static int	fill_cmd(t_cmd *cmd, t_token_list **token)
{
	// TODO
}

static t_cmd	*get_next_cmd(t_token_list **token)
{
	t_cmd			*cmd;
	t_token_id		token_id;

	if (!token && !*token)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd));
	token_id = ((t_token *)((*token)->content))->id;
	while (token_id != TOKEN_PIPE && token_id != TOKEN_AND
		&& token_id != TOKEN_OR)
	{
		if (!fill_cmd(cmd, token))
			return (NULL);
		token_id = ((t_token *)((*token)->content))->id;
	}
	if (token_id == TOKEN_PIPE)
		++(*token);
	return (cmd);
}

static t_cmd_list	*get_next_cmd_list(t_token_list **token)
{
	t_cmd_list	*cmd_list;
	t_cmd_list	*cmd_list_node;
	t_cmd		*cmd;

	cmd_list = NULL;
	while (((t_token *)((*token)->content))->id != TOKEN_AND
		|| ((t_token *)((*token)->content))->id != TOKEN_OR
		|| ((t_token *)((*token)->content))->id != TOKEN_NEW_LINE)
	{
		cmd = get_next_cmd(token);
		if (!cmd)
		{
			// TODO destroy cmd_list
			return (NULL);
		}
		cmd_list_node = ft_lstnew(cmd);
		if (!cmd_list_node)
		{
			// TODO destroy cmd
			// TODO destroy cmd_list
			return (NULL);
		}
		ft_lstadd_back(&cmd_list, cmd_list_node);
	}
	return (cmd_list);
}

t_pipeline_list	*get_next_pipeline(t_token_list **token)
{
	t_pipeline_list	*pipeline_list_node;
	t_cmd_list		*cmd_list;
	t_token_id		token_id;

	if (!token || !*token)
		return (NULL);
	token_id = ((t_token *)((*token)->content))->id;
	if (token_id == TOKEN_AND || token_id == TOKEN_OR
		|| token_id == TOKEN_NEW_LINE)
	{
		// TODO UNEXPECTED TOKEN ERROR
		return (NULL);
	}
	cmd_list = get_next_cmd_list(token);
	if (!cmd_list)
		return (NULL);
	pipeline_list_node = ft_lstnew(cmd_list);
	if (!pipeline_list_node)
		// TODO destroy cmd_list
	return (pipeline_list_node);
}
