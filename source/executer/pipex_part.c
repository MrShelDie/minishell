/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/30 18:54:15 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <stdlib.h>
#include <sys/wait.h>

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
		ft_strdel(&command);
		paths++;
	}
	return (NULL);
}

int    child(
    t_pipe *pipex, t_shell_data *data, t_cmd_list *cmd_list, int i)
{
    int exit_builtin;

    if (dup_tube_and_redir(pipex, data, cmd_list, i) == 1)
        return (1);
    if (((t_cmd *)(cmd_list->content))->is_subshell)
    {
        shell(data, ((t_vector *)((t_cmd *)cmd_list->content)->argv)->data[0]);
        //TODO exit status code
        exit(0);
    }
    pipex->cmd = get_cmd(pipex->cmd_path, ((t_vector *)((t_cmd *)cmd_list->content)->argv)->data[0]);
    if (!pipex->cmd)
    {
		delete_all_pipex_struct(pipex);
        // TODO set exit status
        exit(0);
    }
    exit_builtin = builtins(data, ((t_cmd *)(cmd_list->content))->argv, pipex);
    if (exit_builtin == CMD_PATH)
    {
        if (execve(pipex->cmd, ((t_vector *)((t_cmd *)cmd_list->content)->argv)->data, data->env_vector->data))
        {
            delete_all_pipex_struct(pipex);
            return (1);
        }
        return (0);
    }
    else if (exit_builtin == FAIL)
        return (1);
    return (0);
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
	close_tube(&pipex);
	waitpid(pipex.pid[i - 1], NULL, 0);
    return (0);
}