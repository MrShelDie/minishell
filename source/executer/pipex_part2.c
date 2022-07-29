/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_part2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/29 19:47:43 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <fcntl.h>
#include <stdlib.h>

int dup_pipe(t_pipe *pipex, size_t i)
{
    if (i == 0)
    {
        if (dup2(pipex->tube[i][1], STDOUT_FILENO) == -1)
            return (1);
    }
    else if (i == pipex->len)
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

int dup_redir(t_pipe *pipex, t_redir_list *redir_list, t_shell_data *data)
{
    while (redir_list)
    {
        if (((t_redir *)redir_list->content)->id == REDIR_IN)
        {
            if (infile(pipex, ((t_redir *)redir_list->content)) == 1)
                return (1);
        }
        else if (((t_redir *)redir_list->content)->id == REDIR_HEREDOC)
        {
            pipex->here_doc = replace_names_in_heredoc(data->env_map, &((t_redir *)redir_list->content)->value);
            if (pipex->here_doc == 1)
                return (1);
            pipex->here_doc = open(((t_redir *)redir_list->content)->value, O_RDONLY);
            unlink(((t_redir *)redir_list->content)->value);
            if (dup2(pipex->here_doc, STDIN_FILENO) == -1)
                return (1);
        }
        else if (((t_redir *)redir_list->content)->id == REDIR_OUT)
        {
            if (outfile(pipex, ((t_redir *)redir_list->content)) == 1)
                 return (1);
        }
        // else if (((t_redir *)redir_list->content)->id == REDIR_OUT_APPEND)
        // {

        // }
        redir_list = redir_list->next;
    }
    return (0);
}

int dup_tube_and_redir( t_pipe *pipex, t_shell_data *data, t_cmd_list *cmd_list, int i)
{
    if (pipex->len > 0 && dup_pipe(pipex, i) == 1)
    {
		delete_all_pipex_struct(pipex);
        return (1);    
    }
    if (dup_redir(pipex, ((t_cmd *)(cmd_list->content))->redir_list, data) == 1)
    {
		delete_all_pipex_struct(pipex);
        return (1);
    }
    close_tube(pipex);
    return (0);
}
