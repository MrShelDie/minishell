/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 18:55:52 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "minishell.h"
#include "parser.h"
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>

int	infile(t_pipe *pipex, t_redir *redir)
{
    if (redir->id == REDIR_IN)
    {
        pipex->in = open(redir->value, O_RDONLY);
        if (pipex->in < 0)
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
        return (0);
    }
    return (1);
}

int	create_pipes(t_pipe *pipex)
{
	int	i;

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
    pipex->len = ft_lstsize(cmd_list) - 1;
    pipex->pid = malloc(sizeof(pid_t) * (pipex->len + 1));
    if (!pipex->pid)
        return (1);
    pipex->path = map_get(data->env_map, "PATH");
    if (!pipex->path)
        return (1);
    pipex->cmd_path = ft_split(pipex->path, ':');
    if (!pipex->cmd_path)
        return (1);
    if (create_pipes(pipex) == 1)
        return (1);
    return (0);
}

int dup_pipe(t_pipe *pipex, int i)
{
    if (i == 0)
    {
        if (dup2(STDOUT_FILENO, pipex->tube[i][1]) == -1)
            return (1);
    }
    else if (i == pipex->len - 1)
    {
        if (dup2(STDIN_FILENO, pipex->tube[i][0]) == -1)
            return (1);
    }
    else
    {
        if (dup2(STDIN_FILENO, pipex->tube[i - 1][0]) == -1
            || dup2(STDOUT_FILENO, pipex->tube[i][1]) == -1)
            return (1);
    }
    return (0);
}

int dup_redir(t_pipe *pipex, t_redir_list *redir_list)
{
    while (redir_list)
    {
        // TODO
        redir_list = redir_list->next;
    }
    return (0);
}

void    child(
    t_pipe *pipex, t_shell_data *data, t_cmd_list *cmd_list, int i)
{
    if (pipex->len > 0 && dup_pipe(pipex, i) == 1)
    {
        // TODO ERROR HANDLE
    }
    if (dup_redir(pipex, ((t_cmd *)(cmd_list->content))->redir_list) == 1)
    {
        // TODO ERROR HANDLE
    }
}

int pipex_part(t_shell_data *data, t_cmd_list *cmd_list)
{
    t_pipe  pipex;
    int  i;

    i = 0;
    if (start_pipex(&pipex, data, cmd_list) == 1)
        return (1);
    while (cmd_list && i < pipex.len)
    {
        // if (infile(&pipex, ((t_cmd *)(cmd_list->content))->redir_list->content) == 1)
        //     return (1);
        // if (outfile(&pipex, ((t_cmd *)(cmd_list->content))->redir_list->content) == 1)
        //     return (1);
        pipex.pid[i] = fork();
        if (pipex.pid[i] == -1)
            return (1);
        if (pipex.pid[i] == 0)
            child(&pipex, data, i);
        cmd_list = cmd_list -> next;
        i++;
    }
}