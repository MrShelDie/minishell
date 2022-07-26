/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:01:27 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/26 22:22:15 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_private.h"
#include <stdlib.h>

int	replace_matched_redir(const t_shell_data *shell_data, const char **pattern)
{
	t_matched	matched;

	ft_bzero(&matched, sizeof(t_matched));
	if (!fill_matched(&matched, pattern))
		return (FAIL);
	if (matched.count > 1)
	{
		// TODO error mesage
		destroy_matched(&matched);
		return (FAIL);
	}
	free(*pattern);
	*pattern = matched.words[0];
	free(matched.words);
	return (SUCCESS);
}
