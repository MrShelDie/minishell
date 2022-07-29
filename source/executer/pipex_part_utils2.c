/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_part_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/29 19:48:14 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <stdlib.h>

void ft_strdel(char **as)
{
    if (*as != NULL)
    {
        free(*as);
        *as = NULL;
    } 
}

void ft_strdel_all(char **as)
{
    int i;

    i = 0;
    while (as[i])
    {
        free(as[i]);
        i++;
    }
    as = NULL;
}

void ft_strdel_all2(int **as)
{
    int i;

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
	while (i < (pipex->len))
	{
		close(pipex->tube[i][0]);
		close(pipex->tube[i][1]);
		i++;
	}
}

void    delete_all_pipex_struct(t_pipe *pipex)
{
    close_tube(pipex);
    if (pipex->in)
        close(pipex->in);
    if (pipex->out) 
        close(pipex->out);
    if (pipex->here_doc)
        close(pipex->here_doc);
    if (pipex->cmd_path)
        ft_strdel_all(pipex->cmd_path);
    if (pipex->pid)
        free(pipex->pid);
    if (pipex->tube)
        ft_strdel_all2(pipex->tube);
}

