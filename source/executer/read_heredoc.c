/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:01:00 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/06 14:15:33 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

static int	read_heredoc(int fd, char *stop_word)
{
	char	*input_here;

	while (true)
	{
		input_here = readline("> ");
		if (!input_here)
		{
			rl_replace_line("", 1);
			return (FAIL);
		}
		ft_putstr_fd(input_here, fd);
		if (ft_strcmp(input_here, stop_word) == 0)
			break ;
		ft_putstr_fd("\n", fd);
		free(input_here);
	}
	free(input_here);
	return (SUCCESS);
}

static int	read_heredoc_in_redir(t_redir *redir)
{
	char	*file_name;
	int		fd;

	file_name = generate_file_name(".heredoc_", redir->value);
	if (!file_name)
		return (1);
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (1);
	if (!read_heredoc(fd, redir->value))
	{
		close(fd);
		unlink (file_name);
		return (FAIL);
	}
	close(fd);
	free(redir->value);
	redir->value = file_name;
	return (SUCCESS);
}

static int	read_heredocs_in_redir_list(t_redir_list *redir_list)
{
	t_redir	*redir;

	while (redir_list)
	{
		redir = (t_redir *)redir_list->content;
		if (redir->id == REDIR_HEREDOC)
		{
			if (!read_heredoc_in_redir(redir))
				return (FAIL);
		}
		redir_list = redir_list->next;
	}
	return (SUCCESS);
}

static int	read_heredocs_in_cmd_list(t_cmd_list *cmd_list)
{
	while (cmd_list)
	{
		if (!read_heredocs_in_redir_list(
				((t_cmd *)cmd_list->content)->redir_list))
			return (FAIL);
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}

int	read_all_heredocs(t_logic_group_list *pipe_group)
{
	while (pipe_group)
	{
		if (!read_heredocs_in_cmd_list(pipe_group->content))
			return (FAIL);
		pipe_group = pipe_group->next;
	}
	return (SUCCESS);
}
