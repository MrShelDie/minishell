/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:26:33 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/07 13:09:05 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "executer_private.h"
#include "shell_signal.h"
#include "minishell.h"
#include "expand.h"
#include "libft.h"

static int	exec_builtin(
	t_shell_data *shell_data, t_cmd *cmd, t_builtin_nb builtin_nb)
{
	int	dupped_io_fd[2];
	int	exit_status;

	if (!save_stdio(dupped_io_fd))
	{
		print_error(strerror(errno));
		return (EXIT_FAILURE);
	}
	if (!dup_redir(cmd->redir_list, shell_data))
	{
		delete_saved_stdio(dupped_io_fd);
		print_error(strerror(errno));
		return (EXIT_FAILURE);
	}
	exit_status = shell_data->builtins[builtin_nb](shell_data, cmd->argv);
	if (!restore_stdio(dupped_io_fd))
	{
		delete_saved_stdio(dupped_io_fd);
		print_error(strerror(errno));
		return (EXIT_FAILURE);
	}
	delete_saved_stdio(dupped_io_fd);
	return (exit_status);
}

static void	check_path_and_exit_on_fail(char *cmd_path)
{
	if (!cmd_path)
	{
		print_error(strerror(errno));
		exit (EXIT_FAILURE);
	}
	else if (access(cmd_path, X_OK) == -1)
	{
		print_error_with_file(cmd_path, strerror(errno));
		exit (127);
	}
}

static int	child(t_shell_data *shell_data, t_cmd *cmd)
{
	char	**cmd_paths;
	char	*cmd_path;

	if (cmd->is_subshell)
		exit(execute_user_input(shell_data, cmd->argv->data[0]));
	cmd_paths = get_cmd_paths(shell_data->env_map);
	if (!cmd_paths)
		exit(EXIT_FAILURE);
	cmd_path = get_cmd(cmd_paths, cmd->argv->data[0]);
	ft_strdel_cmd_paths(cmd_paths);
	check_path_and_exit_on_fail(cmd_path);
	if (!dup_redir(cmd->redir_list, shell_data))
		exit (EXIT_FAILURE);
	execve(cmd_path, cmd->argv->data, shell_data->env_vector->data);
	free(cmd_path);
	print_error_with_file(cmd->argv->data[0], strerror(errno));
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
	return (exit_status >> 8);
}

int	execute_simple_cmd(t_shell_data *shell_data, t_logic_group_list *pipe_group)
{
	t_cmd_list		*cmd_list;
	t_cmd			*cmd;
	t_builtin_nb	builtin_nb;

	cmd_list = pipe_group->content;
	cmd = cmd_list->content;
	if (!expand_cmd(shell_data, cmd))
		return (EXIT_FAILURE);
	if (!cmd->arg_list)
		return (EXIT_SUCCESS);
	builtin_nb = get_builtin_nb(cmd->argv->data[0]);
	if (builtin_nb == BUILTIN_NONE || cmd->is_subshell)
		return (exec_util(shell_data, cmd));
	else
		return (exec_builtin(shell_data, cmd, builtin_nb));
}
