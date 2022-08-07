/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/08/07 18:29:15 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <stdlib.h>

void	ft_strdel_cmd_paths(char **as)
{
	int	i;

	if (!as)
		return ;
	i = 0;
	while (as[i])
	{
		free(as[i]);
		i++;
	}
	free(as);
}

void	ft_strdel_tube(int **as, size_t size)
{
	size_t	i;

	if (!as)
		return ;
	i = -1;
	while (++i < size)
		free(as[i]);
	free(as);
}

void	close_tube(t_pipe *pipex)
{
	size_t	i;

	i = 0;
	while (i < (pipex->pipe_count))
	{
		close(pipex->tube[i][0]);
		close(pipex->tube[i][1]);
		i++;
	}
}

void	destroy_pipex(t_pipe *pipex)
{
	free(pipex->pids);
	ft_strdel_cmd_paths(pipex->cmd_path);
	ft_strdel_tube(pipex->tube, pipex->pipe_count);
}
