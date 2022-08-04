/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:01:27 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 17:40:56 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../expand_private.h"
#include "shell_error.h"

int	replace_matched_redir(void **redir_value, bool *asterisk_map)
{
	t_list	*matched_dir_list;

	matched_dir_list = NULL;
	if (!get_matched_dir_name_list(
			&matched_dir_list, *(char **)redir_value, asterisk_map))
		return (FAIL);
	if (!matched_dir_list)
		return (SUCCESS);
	if (matched_dir_list->next)
	{
		print_error_ambiguous_redirect(*(char **)redir_value);
		return (FAIL);
	}
	free(*redir_value);
	*redir_value = matched_dir_list->content;
	free(matched_dir_list);
	return (SUCCESS);
}
