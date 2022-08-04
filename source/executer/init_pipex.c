/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/08/04 15:51:14 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

int	malloc_tube(t_pipe *pipex)
{
	size_t	i;
	bool	flg;

	i = 0;
	flg = true;
	if (!pipex->tube)
		return (1);
	while (i < pipex->pipe_count && flg == true)
	{
		pipex->tube[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipex->tube[i])
			flg = false;
		i++;
	}
	if (flg == false)
	{
		ft_strdel_tube(pipex->tube);
		print_error(strerror(errno));
		return (1);
	}
	return (0);
}

int	create_pipes(t_pipe *pipex)
{
	size_t	i;

	i = 0;
	if (pipex->pipe_count == 0)
		return (0);
	pipex->tube = (int **)ft_calloc(pipex->pipe_count, sizeof(int *));
	if (malloc_tube(pipex) == 1)
		return (1);
	while (i < pipex->pipe_count)
	{
		if (pipe(pipex->tube[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_pipex(t_pipe *pipex, t_shell_data *data, t_cmd_list *cmd_list)
{
	ft_bzero(pipex, sizeof(t_pipe));
	pipex->pipe_count = ft_lstsize(cmd_list) - 1;
	pipex->pids = malloc(sizeof(pid_t) * (pipex->pipe_count + 1));
	if (!pipex->pids)
		return (FAIL);
	pipex->cmd_path = get_cmd_paths(data->env_map);
	if (!pipex->cmd_path)
		return (FAIL);
	if (create_pipes(pipex) == 1)
		return (FAIL);
	return (SUCCESS);
}
