/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:26:33 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/31 22:35:10 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <stdlib.h>

int exec_pipe_group(t_shell_data *shell_data, t_cmd_list *cmd_list)
{
	int 			exit_builtin;
	t_builtin_idx	builtin_idx;

	// TODO 
	
	if (cmd->is_subshell)
	{
		shell(shell_data, cmd->argv->data[0]);
		//TODO exit status code
		exit(EXIT_FAILURE);
	}
	builtin_idx = get_builtin_idx(cmd->argv->data[0]);
	if (builtin_idx == NONE)
	{
		pipex->cmd = get_cmd(pipex->cmd_path, cmd->argv->data[0]);
		if (!pipex->cmd)
		{
			destroy_pipex(pipex);
			// TODO set exit status
			exit(EXIT_FAILURE);
		}
		execve(pipex->cmd, cmd->argv->data, shell_data->env_vector->data);
		destroy_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	exit_builtin =
		shell_data->builtins[builtin_idx](shell_data, cmd->argv->data);
	if (exit_builtin == FAIL)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
