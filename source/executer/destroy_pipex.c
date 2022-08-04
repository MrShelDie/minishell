/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/08/04 15:43:05 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <stdlib.h>

void	ft_strdel_cmd_path(char **as)
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
	as = NULL;
}

void	ft_strdel_tube(int **as)
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
	as = NULL;
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
	close_tube(pipex);
	free(pipex->pids);
	ft_strdel_cmd_path(pipex->cmd_path);
	ft_strdel_tube(pipex->tube);
}
