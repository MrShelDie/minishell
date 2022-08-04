/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_dir_name_to_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:40:47 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 17:31:39 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "../expand_private.h"
#include "shell_error.h"

static int	appeend_dir_name_to_list(
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

int	append_exposed_dir_name_to_list(
	t_list **matched_dir_list, DIR *dir, const t_dirent *dirent)
{
	int	previous_errno;

	while (dirent)
	{
		if (dirent->d_name[0] != '.')
		{
			if (!appeend_dir_name_to_list(matched_dir_list, dirent))
				return (FAIL);
		}
		previous_errno = errno;
		dirent = readdir(dir);
		if (!dirent && previous_errno != errno)
		{
			print_error(strerror(errno));
			return (FAIL);
		}
	}
	return (SUCCESS);
}

int	append_hidden_dir_name_to_list(
	t_list **matched_dir_list, DIR *dir, const t_dirent *dirent)
{
	int	previous_errno;

	while (dirent)
	{
		if (dirent->d_name[0] == '.'
			&& ft_strncmp(dirent->d_name, ".", 2) != 0
			&& ft_strncmp(dirent->d_name, "..", 2) != 0)
		{
			if (!appeend_dir_name_to_list(matched_dir_list, dirent))
				return (FAIL);
		}
		previous_errno = errno;
		dirent = readdir(dir);
		if (!dirent && previous_errno != errno)
		{
			print_error(strerror(errno));
			return (FAIL);
		}
	}
	return (SUCCESS);
}
