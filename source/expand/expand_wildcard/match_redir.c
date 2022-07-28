/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:01:27 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/28 20:52:52 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"
#include <stdlib.h>

int	replace_matched_redir(const t_shell_data *shell_data,
	void **redir_value, bool *asterisk_map)
{
	t_list	*matched_dir_list;
	char	**_redir_value;

	_redir_value = (char **)redir_value;
	if (!get_matched_dir_name_list(&matched_dir_list, *_redir_value, asterisk_map))
		return (FAIL);
	if (!matched_dir_list)
		return (SUCCESS);
	if (matched_dir_list->next)
	{
		(void)shell_data;
		// TODO ambigious redirect
		return (FAIL);
	}
	free(*redir_value);
	*redir_value = matched_dir_list->content;
	free(matched_dir_list);
	return (SUCCESS);
}
