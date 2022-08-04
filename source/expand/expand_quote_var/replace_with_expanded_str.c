/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_with_expanded_str.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:54:24 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 16:36:42 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "../expand_private.h"
#include "shell_error.h"

int	replace_with_expanded_str(
	const t_shell_data *shell_data, void **str)
{
	char	*str_start;
	char	*expanded;

	str_start = *str;
	expanded = ft_strdup("");
	if (!expanded)
	{
		print_error(strerror(errno));
		return (FAIL);
	}
	while (**(char **)str)
	{
		if (!append_regular_str(&expanded, (char **)str))
			return (FAIL);
		if (!**(char **)str)
			break ;
		if (!append_expanded_str(shell_data, &expanded, (char **)str))
			return (FAIL);
	}
	free(str_start);
	*str = expanded;
	return (SUCCESS);
}
