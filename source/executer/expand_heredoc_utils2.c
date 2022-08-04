/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:18:22 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 20:23:46 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

static int	open_fds(const char *old_file_name, char *new_file_name)
{
	if (!new_file_name)
		return (-1);
	if (access(old_file_name, 0) == -1)
	{
		print_error_with_file(old_file_name, strerror(errno));
		return (-1);
	}
	return (open(old_file_name, O_RDONLY));
}

char	*open_files(const char *old_file_name, int *old_fd, int *new_fd)
{
	char	*new_file_name;

	new_file_name = ft_strjoin(old_file_name, "_exp");
	*old_fd = open_fds(old_file_name, new_file_name);
	if (*old_fd < 0)
	{
		free(new_file_name);
		print_error(strerror(errno));
		return (NULL);
	}
	unlink(old_file_name);
	*new_fd = open(new_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (*new_fd < 0)
	{
		close(*old_fd);
		free(new_file_name);
		print_error(strerror(errno));
		return (NULL);
	}
	return (new_file_name);
}
