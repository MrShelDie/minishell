/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logic_group_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:01:48 by medric            #+#    #+#             */
/*   Updated: 2022/08/07 11:18:24 by gannemar         ###   ########.fr       */
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

int	wait_all_pids(pid_t *pids, size_t size)
{
	size_t	i;
	int		exit_status;

	i = -1;
	while (++i < size)
		waitpid(pids[i], &exit_status, 0);
	return (exit_status >> 8);
}

int	exec_init_pipex(t_pipe *pipex,
			t_shell_data *data, t_cmd_list *cmd_list)
{
	if (!init_pipex(pipex, data, cmd_list))
	{
		close_tube(pipex);
		destroy_pipex(pipex);
		print_error(strerror(errno));
		return (FAIL);
	}
	return (SUCCESS);
}

static void	handle_error(t_pipe *pipex)
{
	print_error(strerror(errno));
	close_tube(pipex);
	destroy_pipex(pipex);
}

void	exec_utils(t_pipe *pipex,
			t_shell_data *shell_data, t_cmd *cmd, int *exit_builtin)
{
	t_builtin_nb	builtin_nb;

	builtin_nb = get_builtin_nb(cmd->argv->data[0]);
	if (builtin_nb == BUILTIN_NONE)
	{
		pipex->cmd = get_cmd(pipex->cmd_path, cmd->argv->data[0]);
		if (!pipex->cmd)
		{
			handle_error(pipex);
			exit(EXIT_FAILURE);
		}
		else if (access(pipex->cmd, X_OK) == -1)
		{
			handle_error(pipex);
			exit(127);
		}
		execve(pipex->cmd, cmd->argv->data, shell_data->env_vector->data);
		print_error(strerror(errno));
		close_tube(pipex);
		destroy_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	*exit_builtin = shell_data->builtins[builtin_nb](shell_data, cmd->argv);
}
