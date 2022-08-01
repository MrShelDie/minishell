/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_group.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/08/01 15:46:23 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <stdlib.h>
#include <sys/wait.h>

static int	dup_tube_and_redir( t_pipe *pipex, t_shell_data *data, t_cmd *cmd, int i)
{
	if (pipex->pipe_count > 0 && dup_pipe(pipex, i) == 1)
	{
		destroy_pipex(pipex);
		return (1);    
	}
	if (!dup_redir(cmd->redir_list, data))
	{
		destroy_pipex(pipex);
		return (1);
	}
	close_tube(pipex);
	return (0);
}

// TODO очистка данных при exit fail
static int    child(
	t_pipe *pipex, t_shell_data *shell_data, t_cmd *cmd, int i)
{
	int 			exit_builtin;
	t_builtin_nb	builtin_nb;

	if (dup_tube_and_redir(pipex, shell_data, cmd, i) == 1)
	{
		// TODO мб чёта написать в СТД-ИН надо
		exit(EXIT_FAILURE);
	}
	if (cmd->is_subshell)
	{
		shell(shell_data, cmd->argv->data[0]);
		//TODO exit status code
		exit(EXIT_FAILURE);
	}
	builtin_nb = get_builtin_nb(cmd->argv->data[0]);
	if (builtin_nb == NONE)
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
		shell_data->builtins[builtin_nb](shell_data, cmd->argv->data);
	if (exit_builtin == FAIL)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int	wait_all_pids(pid_t *pids, size_t size)
{
	size_t	i;
	int		exit_status;

	i = -1;
	while (++i < size)
		waitpid(pids[i], &exit_status, 0);
	return (exit_status);
}

int exec_pipe_group(t_shell_data *data, t_cmd_list *cmd_list)
{
	t_pipe  pipex;
	size_t  i;
	int		exit_status;

	if (!init_pipex(&pipex, data, cmd_list))
	{
		destroy_pipex(&pipex);
		return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < pipex.pipe_count + 1)
	{
		pipex.pids[i] = fork();
		if (pipex.pids[i] == -1)
		{
			destroy_pipex(&pipex);
			return (EXIT_FAILURE);
		}
		if (pipex.pids[i] == 0)
			child(&pipex, data, cmd_list->content, i);
		cmd_list = cmd_list->next;
	}
	exit_status = wait_all_pids(pipex.pids, pipex.pipe_count + 1);
	destroy_pipex(&pipex);
	return (exit_status);
}
