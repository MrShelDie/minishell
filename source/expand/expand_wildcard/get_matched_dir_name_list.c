/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matched_dir_name_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:52:01 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/28 20:52:06 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

static int  append_dir_name_to_list(
	t_list **matched_dir_list, const t_dirent *dirent)
{
	char	*d_name_copy;
	t_list	*new;

	d_name_copy = ft_strdup(dirent->d_name);
	if (!d_name_copy)
	{
		ft_lstclear(matched_dir_list, free);
		return (FAIL);
	}
	new = ft_lstnew(d_name_copy);
	if (!new)
	{
		free(d_name_copy);
		ft_lstclear(matched_dir_list, free);
		return (FAIL);
	}
	ft_lstadd_back(matched_dir_list, new);
	return (SUCCESS);
}

static int	fill_dir_name_list(t_list **matched_dir_list, const char *cwd)
{
	DIR         *dir;
	t_dirent    *dirent;

	dir = opendir(cwd);
	if (!dir)
		return (FAIL);
	dirent = readdir(dir);
	while (dirent)
	{
		if (!append_dir_name_to_list(matched_dir_list, dirent))
		{
			closedir(dir);
			return (FAIL);
		}
		dirent = readdir(dir);
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
	if (!fill_dir_name_list(matched_dir_list, cwd))
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
