/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:26:33 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/03 11:09:20 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "executer_private.h"
#include "minishell.h"
#include "expand.h"
#include "libft.h"

static void	delete_saved_stdio(int dupped_io_fd[2])
{
	if (dupped_io_fd[STDIN_FILENO] != -1)
		close(dupped_io_fd[STDIN_FILENO]);
	if (dupped_io_fd[STDOUT_FILENO] != -1)
		close(dupped_io_fd[STDOUT_FILENO]);
}

static int	save_stdio(int dupped_io_fd[2])
{
	dupped_io_fd[STDIN_FILENO] = dup(STDIN_FILENO);
	if (dupped_io_fd[STDIN_FILENO] == -1)
		return (FAIL);
	dupped_io_fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (dupped_io_fd[STDOUT_FILENO] == -1)
	{
		close(dupped_io_fd[STDIN_FILENO]);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	restore_stdio(int dupped_io_fd[2])
{
	bool	error_occurred;

	error_occurred = false;
	if (dup2(dupped_io_fd[STDIN_FILENO], STDIN_FILENO) == -1)
		error_occurred = true;
	if (dup2(dupped_io_fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
		error_occurred = true;
	if (error_occurred)
		return (FAIL);
	return (SUCCESS);
}

static int	exec_builtin(
	t_shell_data *shell_data, t_cmd *cmd, t_builtin_nb builtin_nb)
{
	int	dupped_io_fd[2];
	int	exit_status;

	if (!save_stdio(dupped_io_fd))
		return (EXIT_FAILURE);
	if (!dup_redir(cmd->redir_list, shell_data))
	{
		delete_saved_stdio(dupped_io_fd);
		return (EXIT_FAILURE);
	}
	exit_status =
		shell_data->builtins[builtin_nb](shell_data, cmd->argv);
	if (!restore_stdio(dupped_io_fd))
	{
		delete_saved_stdio(dupped_io_fd);
		return (EXIT_FAILURE);
	}
	delete_saved_stdio(dupped_io_fd);
	return (exit_status);
}

static int	child(t_shell_data *shell_data, t_cmd *cmd)
{
	char	**cmd_paths;
	char	*cmd_path;

	cmd_paths = get_cmd_paths(shell_data->env_map);
	if (!cmd_paths)
		exit(EXIT_FAILURE);
	cmd_path = get_cmd(cmd_paths, cmd->argv->data[0]);
	ft_strdel_cmd_path(cmd_paths);
	if (!cmd)
		exit (EXIT_FAILURE);
	if (!dup_redir(cmd->redir_list, shell_data))
		exit (EXIT_FAILURE);
	execve(cmd_path, cmd->argv->data, shell_data->env_vector->data);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

static int	exec_util(t_shell_data *shell_data, t_cmd *cmd)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
		child(shell_data, cmd);
	waitpid(pid, &exit_status, 0);
	return (exit_status);
}

int execute_simple_cmd(t_shell_data *shell_data, t_pipe_group_list *pipe_group)
{
	t_cmd_list		*cmd_list;
	t_cmd			*cmd;
	t_builtin_nb	builtin_nb;

	cmd_list = pipe_group->content;
	cmd = cmd_list->content;
	expand_cmd(shell_data, cmd);
	if (!cmd->arg_list)
		return (EXIT_SUCCESS);
	builtin_nb = get_builtin_nb(cmd->argv->data[0]);
	if (builtin_nb != BUILTIN_NONE)
		return (exec_builtin(shell_data, cmd, builtin_nb));
	else
		return (exec_util(shell_data, cmd));
}
