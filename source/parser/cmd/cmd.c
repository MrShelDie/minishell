/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:40:52 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/19 20:41:25 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser_private.h"
#include <stdlib.h>

static int	fill_cmd(t_cmd *cmd, t_token_list **token)
{
	t_token_id		token_id;

	token_id = ((t_token *)((*token)->content))->id;
	if (token_id == TOKEN_ANG_BR_L)
		return (fill_redir(cmd, token, REDIR_IN));
	else if (token_id == TOKEN_D_ANG_BR_L)
		return (fill_redir(cmd, token, REDIR_HEREDOC));
	else if (token_id == TOKEN_ANG_BR_R)
		return (fill_redir(cmd, token, REDIR_OUT));
	else if (token_id == TOKEN_D_ANG_BR_R)
		return (fill_redir(cmd, token, REDIR_OUT_APPEND));
	else if (token_id == TOKEN_PAR_L && cmd->argv->length == 0)
		return (fill_subshell(cmd, token));
	else if (token_id == TOKEN_WORD)
		return (fill_argv(cmd, token));
	else
	{
		write_unexpected_token_error(token_id);
		return (FAIL);
	}
}

static t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->argv = vector_create();
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

void	destroy_cmd(void *cmd)
{
	vector_destroy(((t_cmd *)cmd)->argv);
	ft_lstclear(&((t_cmd *)cmd)->redir_list, destroy_redir);
}

t_cmd	*get_next_cmd(t_token_list **token)
{
	t_cmd			*cmd;
	t_token_id		token_id;

	if (!token && !*token)
		return (NULL);
	token_id = ((t_token *)((*token)->content))->id;
	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	while (token_id != TOKEN_PIPE && token_id != TOKEN_AND
		&& token_id != TOKEN_OR && token_id != TOKEN_NEW_LINE)
	{
		if (!fill_cmd(cmd, token))
			return (NULL);
		token_id = ((t_token *)((*token)->content))->id;
	}
	return (cmd);
}
