/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matched_dir_name_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:52:01 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 17:32:30 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "../expand_private.h"
#include "shell_error.h"

static int	remove_unmatched_dirs(
	t_list **matched_dir_list, const char *pattern, bool *asterisk_map)
{
	t_list	**current;
	t_list	*next;
	int		err;

	err = SUCCESS;
	current = matched_dir_list;
	while (*current)
	{
		next = (*current)->next;
		if (!is_matched((*current)->content, pattern, asterisk_map, &err)
			&& err != FAIL)
		{
			ft_lstdelone(*current, free);
			*current = next;
			continue ;
		}
		if (err == FAIL)
			return (FAIL);
		current = &(*current)->next;
	}
	return (SUCCESS);
}

static int	fill_dir_name_list(
	t_list **matched_dir_list, const char *cwd, bool is_hidden_directories)
{
	DIR			*dir;
	t_dirent	*dirent;
	int			previous_errno;
	int			append_status;

	dir = opendir(cwd);
	if (!dir)
	{
		print_error(strerror(errno));
		return (FAIL);
	}
	previous_errno = errno;
	dirent = readdir(dir);
	if (!dirent && previous_errno != errno)
		print_error(strerror(errno));
	append_status = FAIL;
	if (dirent && is_hidden_directories)
		append_status = append_hidden_dir_name_to_list(
				matched_dir_list, dir, dirent);
	else if (dirent && !is_hidden_directories)
		append_status = append_exposed_dir_name_to_list(
				matched_dir_list, dir, dirent);
	closedir(dir);
	return (append_status);
}

int	get_matched_dir_name_list(
	t_list **matched_dir_list, const char *pattern, bool *asterisk_map)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		print_error(strerror(errno));
		return (FAIL);
	}
	if (!fill_dir_name_list(matched_dir_list, cwd, pattern[0] == '.')
		|| !remove_unmatched_dirs(matched_dir_list, pattern, asterisk_map))
	{
		free(cwd);
		ft_lstclear(matched_dir_list, free);
		return (FAIL);
	}
	free(cwd);
	return (SUCCESS);
}
