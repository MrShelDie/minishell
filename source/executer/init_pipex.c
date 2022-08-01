/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/08/01 15:51:55 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <stdio.h>
#include <stdlib.h>

int	create_pipes(t_pipe *pipex)
{
	size_t	i;

	i = 0;
	if (pipex->pipe_count == 0)
		return (0);
	pipex->tube = (int **)ft_calloc(pipex->pipe_count, sizeof(int *));
	if (!pipex->tube)
		return (1);
	while (i < pipex->pipe_count)
	{
		pipex->tube[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipex->tube[i])
			return (1);
		i++;
	}
	i = 0;
	while (i < pipex->pipe_count)
	{
		if (pipe(pipex->tube[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int    init_pipex(t_pipe *pipex, t_shell_data *data, t_cmd_list *cmd_list)
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
