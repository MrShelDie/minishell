/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/28 20:21:27 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "minishell.h"
#include "parser.h"
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>

int	builtins(t_shell_data *shell_data, t_vector *cmd, t_pipe *pipex)
{
	int	i;

	i = 0;
	// if (cmd->data[i] == NULL)
	// 	return (FAIL);
	if (ft_strncmp(cmd->data[i], "echo", 4) == 0)
	{
		i++;
		if (ft_echo(cmd->data, i, pipex->out) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	else if (ft_strncmp(cmd->data[i], "pwd", 3) == 0)
	{
		i++;
		if (ft_pwd() == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	else if (ft_strncmp(cmd->data[i], "env", 3) == 0)
	{
		i++;
		if (ft_env(shell_data->env_map->head) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	else if (ft_strncmp(cmd->data[i], "cd", 2) == 0)
	{
		i++;
		if (ft_cd(cmd->data, shell_data) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	else if (ft_strncmp(cmd->data[i], "unset", 5) == 0)
	{
		i++;
		if (ft_unset(cmd->data, shell_data) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	else if (ft_strncmp(cmd->data[i], "export", 6) == FAIL)
	{
		if (ft_export(cmd, shell_data) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	return (CMD_PATH);
}

int	create_heredoc_names(t_cmd_list *cmd_list)
{
	t_redir_list	*redir_list;

	while (cmd_list)
	{
		redir_list = ((t_cmd *)cmd_list->content)->redir_list;
		while (redir_list)
		{
			if (((t_redir *)redir_list->content)->id == REDIR_HEREDOC)
			{
				if (create_heredoc(&((t_redir *)redir_list->content)->value) == 1)
					return (1);
			}
			redir_list = redir_list->next;
		}
		cmd_list = cmd_list -> next;
	}
	return (0);
}


///TODO chto esli ne zapisalis' dannye
void	 quite_heredoc(t_pipe_group_list *pipe_group)
{
	while (pipe_group)
	{
		create_heredoc_names((t_cmd_list *)pipe_group->content);
		pipe_group = pipe_group->next;
	}
}

void	executer(t_shell_data *shell_data, t_parsed_data *parsed_data)
{
	t_pipe_group_list	*pipe_group;
	t_operator_list		*operator;
	int					exit_status;

	pipe_group = parsed_data->pipe_group_list;
	operator = parsed_data->operator_list;
	quite_heredoc(pipe_group);
	while (pipe_group)
	{
		// TODO PIPE GROUP PREPARE

		exit_status = pipex_part(
				shell_data, (t_cmd_list *)pipe_group->content);
		pipe_group = pipe_group->next;
		if ((*(t_operator *)operator->content == OP_AND && exit_status != 0)
			|| (*(t_operator *)operator->content == OP_OR && exit_status == 0))
			pipe_group = pipe_group->next;
		if (*(t_operator *)operator->content == OP_NEW_LINE)
			return ;
		operator = operator->next;
	}
}
