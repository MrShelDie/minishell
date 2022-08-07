/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:40:52 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/07 18:18:04 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "../parser_private.h"
#include "shell_error.h"

static int	fill_cmd(t_cmd *cmd, t_token_list **token, size_t *recursion_level)
{
	t_token_id		token_id;

	token_id = ((t_token *)((*token)->content))->id;
	if (token_id == TOKEN_ANG_BR_L)
		return (fill_redir(cmd, token, REDIR_IN, recursion_level));
	else if (token_id == TOKEN_D_ANG_BR_L)
		return (fill_redir(cmd, token, REDIR_HEREDOC, recursion_level));
	else if (token_id == TOKEN_ANG_BR_R)
		return (fill_redir(cmd, token, REDIR_OUT, recursion_level));
	else if (token_id == TOKEN_D_ANG_BR_R)
		return (fill_redir(cmd, token, REDIR_OUT_APPEND, recursion_level));
	else if (token_id == TOKEN_PAR_L && ft_lstsize(cmd->arg_list) == 0)
		return (fill_subshell(cmd, token, recursion_level));
	else if (token_id == TOKEN_WORD && cmd->is_subshell == false)
		return (fill_arg_list(cmd, token));
	else
	{
		unexpected_token_error((*token)->content, *recursion_level);
		return (FAIL);
	}
}

static t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		print_error(strerror(errno));
		return (NULL);
	}
	return (cmd);
}

void	destroy_cmd(void *cmd)
{
	vector_destroy(((t_cmd *)cmd)->argv);
	ft_lstclear(&((t_cmd *)cmd)->redir_list, destroy_redir);
	ft_lstclear(&((t_cmd *)cmd)->arg_list, free);
	free(cmd);
}

t_cmd	*get_next_cmd(t_token_list **token_list_node, size_t *recursion_level)
{
	t_cmd			*cmd;
	t_token_id		token_id;

	if (!token_list_node && !*token_list_node)
		return (NULL);
	token_id = ((t_token *)((*token_list_node)->content))->id;
	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	while (token_id != TOKEN_PIPE && token_id != TOKEN_AND
		&& token_id != TOKEN_OR && token_id != TOKEN_NEW_LINE)
	{
		if (!fill_cmd(cmd, token_list_node, recursion_level))
			return (NULL);
		token_id = ((t_token *)((*token_list_node)->content))->id;
	}
	return (cmd);
}
