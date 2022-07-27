/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:01:27 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/27 17:06:37 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"
#include <stdlib.h>

int	replace_matched_redir(
	const t_shell_data *shell_data, const char **redir_value)
{	
	t_list	*matched_dir_list;

	if (!get_matched_dir_name_list(&matched_dir_list, redir_value))
		return (FAIL);
	if (!matched_dir_list)
		return (SUCCESS);
	if (matched_dir_list->next)
	{
		// TODO ambigious redirect
		return (FAIL);
	}
	free(*redir_value);
	*redir_value = matched_dir_list->content;
	free(matched_dir_list);
	return (SUCCESS);
}
