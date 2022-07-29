/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_part_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/29 19:43:31 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int	infile(t_pipe *pipex, t_redir *redir)
{
    if (redir->id == REDIR_IN)
    {
        pipex->in = open(redir->value, O_RDONLY);
        if (pipex->in < 0)
            return (1);
        if (dup2(pipex->in, STDIN_FILENO) == -1)
            return (1);
        return (0);
    }
    return (1);
}

int	outfile(t_pipe *pipex, t_redir *redir)
{
    if (redir->id == REDIR_OUT)
    {
		pipex->out = open(redir->value, O_TRUNC | O_CREAT | O_RDWR, 0666);
	    if (pipex->out < 0)
		    return (1);
        if (pipex->len > 0)
        {
            if (dup2(pipex->out, STDOUT_FILENO) == -1)
                return (1);
        }
        return (0);
    }
    return (1);
}

int	create_pipes(t_pipe *pipex)
{
	size_t	i;

	i = 0;
	pipex->tube = (int **)malloc(sizeof(int *) * (pipex->len));
	if (!pipex->tube)
		return (1);
	while (i < pipex->len)
	{
		pipex->tube[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipex->tube[i])
		    return (1);
		i++;
	}
	i = 0;
	while (i < pipex->len)
	{
		if (pipe(pipex->tube[i]) < 0)
		    return (1);
		i++;
	}
    return (0);
}

int    start_pipex(t_pipe *pipex, t_shell_data *data, t_cmd_list *cmd_list)
{
    pipex->in = 0;
    pipex->out = 0;
    pipex->len = ft_lstsize(cmd_list) - 1;
    pipex->pid = malloc(sizeof(pid_t) * (pipex->len + 1));
    if (!pipex->pid)
        return (1);
    pipex->path = (char *)map_get(data->env_map, "PATH");
    if (!pipex->path)
        return (1);
    pipex->cmd_path = ft_split(pipex->path, ':');
    if (!pipex->cmd_path)
        return (1);
    if (create_pipes(pipex) == 1)
        return (1);
    return (0);
}
