/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/25 20:31:52 by gannemar         ###   ########.fr       */
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

#include <sys/types.h>
#include <sys/wait.h>

int	infile(t_pipe *pipex, t_redir *redir)
{
    if (redir->id == REDIR_IN)
    {
        pipex->in = open(redir->value, O_RDONLY);
        if (pipex->in < 0)
            return (1);
        // TODO ERROR HANDLER
        dup2(pipex->in, STDIN_FILENO);
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
        // TODO ERROR HANDLER
        dup2(pipex->out, STDOUT_FILENO);
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
    pipex->len = ft_lstsize(cmd_list) - 1;
    pipex->pid = malloc(sizeof(pid_t) * (pipex->len + 1));
    if (!pipex->pid)
        return (1);
    pipex->path = (char *)map_get(data->env_map, "PATH");
    ///NOT DELETE!!!!!!!!!!!!!!!!!!!! path
    if (!pipex->path)
        return (1);
    pipex->cmd_path = ft_split(pipex->path, ':');
    if (!pipex->cmd_path)
        return (1);
    if (create_pipes(pipex) == 1)
        return (1);
    return (0);
}

int dup_pipe(t_pipe *pipex, size_t i)
{
    if (i == 0)
    {
        if (dup2(pipex->tube[i][1], STDOUT_FILENO) == -1)
            return (1);
    }
    else if (i == pipex->len)
    {
		//write(2, "b", 1);
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

int dup_redir(t_pipe *pipex, t_redir_list *redir_list)
{
    while (redir_list)
    {
        if (((t_redir *)redir_list->content)->id == REDIR_IN)
        {
            if (infile(pipex, ((t_redir *)redir_list->content)) == 1)
                return (1);
        }
        else if (((t_redir *)redir_list->content)->id == REDIR_OUT)
        {
            if (outfile(pipex, ((t_redir *)redir_list->content)) == 1)
                 return (1);
        }
        // TODO HEREDOC, WRITE_APPEND
        redir_list = redir_list->next;
    }
    return (0);
}

void	ft_strdel(char **as)
{
	if (as != NULL)
	{
		free(*as);
		*as = NULL;
	}
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		ft_strdel(&tmp);
		if (access(command, 0) == 0)
			return (command);
		//ft_strdel(&command);
		paths++;
	}
	return (NULL);
}

void	close_tube(t_pipe *pipex)
{
	size_t	i;

	i = 0;
	while (i < (pipex->len))
	{
		close(pipex->tube[i][0]);
		close(pipex->tube[i][1]);
		i++;
	}
}

void    child(
    t_pipe *pipex, t_shell_data *data, t_cmd_list *cmd_list, int i)
{
	// write(2, "a", 1);
    if (pipex->len > 0)
    {
		// write(2, "ccc", 3);
		dup_pipe(pipex, i);
        // TODO ERROR HANDLE
    }
    if (dup_redir(pipex, ((t_cmd *)(cmd_list->content))->redir_list) == 1)
    {
		// TODO DELETE
		write(2, "b", 1);
        // TODO ERROR HANDLE
    }
	// write(2, "AAA", 3);
    close_tube(pipex);
    pipex->cmd = get_cmd(pipex->cmd_path, ((t_vector *)((t_cmd *)cmd_list->content)->argv)->data[0]);
    execve(pipex->cmd, ((t_vector *)((t_cmd *)cmd_list->content)->argv)->data, data->env_vector->data);
		//TODO handel error
    //     return (1);
    // return (0);
}

int pipex_part(t_shell_data *data, t_cmd_list *cmd_list)
{
    t_pipe  pipex;
    size_t  i;

    i = 0;
    if (start_pipex(&pipex, data, cmd_list) == 1)
        return (1);
    while (cmd_list)
    {
        pipex.pid[i] = fork();
        if (pipex.pid[i] == -1)
            return (1);
        if (pipex.pid[i] == 0)
            child(&pipex, data, cmd_list, i);
        cmd_list = cmd_list -> next;
        i++;
    }
	// ВРЕМЕМЕННОЕ РЕШЕНИЕ
	// waitpid(pipex.pid[i - 2], NULL, 0);
	close_tube(&pipex);
	waitpid(pipex.pid[i - 1], NULL, 0);
    return (0);
}