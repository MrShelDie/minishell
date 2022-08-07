/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:33:48 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/07 15:46:24 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "parser_private.h"

static void	unlink_heredoc_in_redir(void *redir)
{
	t_redir_id	id;
	char		*value;

	id = ((t_redir *)redir)->id;
	value = ((t_redir *)redir)->value;
	if (id == REDIR_HEREDOC && access(value, R_OK) != -1)
		unlink(value);
}

static void	unlink_heredoc_in_cmd(void *cmd)
{
	ft_lstiter(((t_cmd *)cmd)->redir_list, unlink_heredoc_in_redir);
}

static void	unlink_heredoc_in_cmd_list(void *cmd_list)
{
	ft_lstiter(cmd_list, unlink_heredoc_in_cmd);
}

void	unlink_heredocs(t_logic_group_list *logic_group_list)
{
	ft_lstiter(logic_group_list, unlink_heredoc_in_cmd_list);
}
