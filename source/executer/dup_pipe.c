/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/08/04 15:43:26 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <fcntl.h>
#include <stdlib.h>

int	dup_pipe(t_pipe *pipex, size_t i)
{
	if (i == 0)
	{
		if (dup2(pipex->tube[i][1], STDOUT_FILENO) == -1)
			return (1);
	}
	else if (i == pipex->pipe_count)
	{
		if (dup2(pipex->tube[i - 1][0], STDIN_FILENO) == -1)
			return (1);
	}
	else
	{
		if (dup2(pipex->tube[i - 1][0], STDIN_FILENO) == -1
			|| dup2(pipex->tube[i][1], STDOUT_FILENO) == -1)
			return (1);
	}
	return (0);
}
