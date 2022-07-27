/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matched_dir_name_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:52:01 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/27 16:57:14 by gannemar         ###   ########.fr       */
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

static void	remove_unmatched_dirs(
	t_list **matched_dir_list, const char *pattern)
{
	t_list	**current;
	t_list	*next;

	current = matched_dir_list;
	while (*current)
	{
		next = (*current)->next;
		if (!is_matched((*current)->content, pattern))
		{
			ft_lstdelone(*current, free);
			*current = next;
			continue ;
		}
		current = &(*current)->next;
	}
}

int	*get_matched_dir_name_list(
	t_list **matched_dir_list, const char *pattern)
{
	char	*cwd;

	cwd = getcwd(cwd, NULL);
	if (!cwd)
	{
		// TODO handle error
		return (NULL);
	}
	if (!fill_dir_name_list(matched_dir_list, cwd))
	{
		free(cwd);
		return (NULL);
	}
	remove_unmatched_dirs(matched_dir_list, pattern);
	free(cwd);
	return (matched_dir_list);
}
