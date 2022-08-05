/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_logic_group.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/08/05 18:29:20 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#include "executer_private.h"
#include "minishell.h"
#include "expand.h"
#include "libft.h"

static int	dup_tube_and_redir( t_pipe *pipex,
					t_shell_data *data, t_cmd *cmd, int i)
{
	if (pipex->pipe_count > 0 && dup_pipe(pipex, i) == 1)
	{
		destroy_pipex(pipex);
		print_error(strerror(errno));
		return (1);
	}
	if (!dup_redir(cmd->redir_list, data))
	{
		destroy_pipex(pipex);
		print_error(strerror(errno));
		return (1);
	}
	close_tube(pipex);
	return (0);
}

static int	child(
	t_pipe *pipex, t_shell_data *shell_data, t_cmd *cmd, int i)
{
	int	exit_builtin;

	if (dup_tube_and_redir(pipex, shell_data, cmd, i) == 1)
	{
		print_error(strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (cmd->is_subshell)
	{
		execute_user_input(shell_data, cmd->argv->data[0]);
		print_error(strerror(errno));
		exit(EXIT_FAILURE);
	}
	exec_utils(pipex, shell_data, cmd, &exit_builtin);
	if (exit_builtin == FAIL)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static int	execute_cmd_list(t_shell_data *data, t_cmd_list *cmd_list)
{
	t_pipe	pipex;
	size_t	i;
	int		exit_status;

	i = -1;
	if (!exec_init_pipex(&pipex, data, cmd_list))
		return (EXIT_FAILURE);
	while (++i < pipex.pipe_count + 1)
	{
		pipex.pids[i] = fork();
		if (pipex.pids[i] == -1)
		{
			destroy_pipex(&pipex);
			print_error(strerror(errno));
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

int	execute_logic_group_list(t_shell_data *shell_data,
	t_logic_group_list *logic_group_list, t_operator_list *operator_list)
{
	t_operator	*operator;
	int			exit_status;

	while (logic_group_list)
	{
		operator = operator_list->content;
		if (!expand_logic_group(shell_data, logic_group_list->content))
			return (EXIT_FAILURE);
		exit_status = execute_cmd_list(shell_data, logic_group_list->content);
		logic_group_list = logic_group_list->next;
		if ((*operator == OP_AND && exit_status != 0)
			|| (*operator == OP_OR && exit_status == 0))
			logic_group_list = logic_group_list->next;
		if (*operator == OP_NEW_LINE)
			break ;
		operator_list = operator_list->next;
	}
	return (exit_status);
}
