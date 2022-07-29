/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matched_dir_name_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:52:01 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/29 17:45:07 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"
#include <stdlib.h>

static int	fill_dir_name_list(
	t_list **matched_dir_list, const char *cwd, bool is_hidden)
{
	DIR         *dir;
	t_dirent    *dirent;

	dir = opendir(cwd);
	if (!dir)
		return (FAIL);
	dirent = readdir(dir);
	if (dirent && !is_hidden
		&& !append_exposed_dir_name_to_list(matched_dir_list, dir, dirent))
	{
		closedir(dir);
		return (FAIL);
	}
	else if (dirent && is_hidden
		&& !append_hidden_dir_name_to_list(matched_dir_list, dir, dirent))
	{
		closedir(dir);
		return (FAIL);
	}
	closedir(dir);
	return (SUCCESS);
}

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

int	get_matched_dir_name_list(
	t_list **matched_dir_list, const char *pattern, bool *asterisk_map)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		// TODO handle error
		return (FAIL);
	}
	if (!fill_dir_name_list(matched_dir_list, cwd, pattern[0] == '.'))
	{
		free(cwd);
		return (FAIL);
	}
	if (!remove_unmatched_dirs(matched_dir_list, pattern, asterisk_map))
	{
		free(cwd);
		ft_lstclear(matched_dir_list, free);		
		return (FAIL);
	}
	free(cwd);
	return (SUCCESS);
}
