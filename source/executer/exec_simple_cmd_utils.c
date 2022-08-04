/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:05:40 by medric            #+#    #+#             */
/*   Updated: 2022/08/04 16:06:49 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "executer_private.h"
#include "minishell.h"
#include "expand.h"
#include "libft.h"

void	delete_saved_stdio(int dupped_io_fd[2])
{
	if (dupped_io_fd[STDIN_FILENO] != -1)
		close(dupped_io_fd[STDIN_FILENO]);
	if (dupped_io_fd[STDOUT_FILENO] != -1)
		close(dupped_io_fd[STDOUT_FILENO]);
}

int	save_stdio(int dupped_io_fd[2])
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

int	restore_stdio(int dupped_io_fd[2])
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