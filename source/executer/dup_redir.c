/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:44:13 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 19:19:06 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_private.h"
#include <fcntl.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

int	dup_infile(const char *file_name)
{
	int	in;

	if (access(file_name, 0) == -1)
	{
		print_error_with_file(file_name, strerror(errno));
		return (FAIL);
	}
	in = open(file_name, O_RDONLY);
	if (in < 0)
		return (FAIL);
	if (dup2(in, STDIN_FILENO) < 0)
	{
		close(in);
		return (FAIL);
	}
	return (SUCCESS);
}

int	dup_heredoc(t_map *env, t_redir *redir)
{
	int		heredoc;

	if (!expand_var_in_heredoc(env, &redir->value))
		return (FAIL);
	heredoc = open(redir->value, O_RDONLY);
	unlink(redir->value);
	if (dup2(heredoc, STDIN_FILENO) < 0)
		return (FAIL);
	return (SUCCESS);
}

int	dup_outfile(const char *file_name)
{
	int	out;

	out = open(file_name, O_TRUNC | O_CREAT | O_WRONLY, 0666);
	if (out < 0)
		return (FAIL);
	if (dup2(out, STDOUT_FILENO) < 0)
		return (FAIL);
	return (SUCCESS);
}

int	dup_outfile_append(const char *file_name)
{
	int	out;

	out = open(file_name, O_APPEND | O_CREAT | O_WRONLY, 0666);
	if (out < 0)
		return (FAIL);
	if (dup2(out, STDOUT_FILENO) < 0)
		return (FAIL);
	return (SUCCESS);
}

int	dup_redir(t_redir_list *redir_list, t_shell_data *data)
{
	t_redir	*redir;

	while (redir_list)
	{
		redir = redir_list->content;
		if (redir->id == REDIR_IN && !dup_infile(redir->value))
			return (FAIL);
		else if (redir->id == REDIR_HEREDOC
			&& !dup_heredoc(data->env_map, redir))
			return (FAIL);
		else if (redir->id == REDIR_OUT
			&& !dup_outfile(redir->value))
			return (FAIL);
		else if (redir->id == REDIR_OUT_APPEND
			&& !dup_outfile_append(redir->value))
			return (FAIL);
		redir_list = redir_list->next;
	}
	return (SUCCESS);
}
