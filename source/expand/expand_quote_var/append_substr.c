/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_substr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:19:42 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 14:52:35 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "../expand_private.h"
#include "shell_error.h"

int	append_substr(char **dst, const char *src, size_t len)
{
	char	*new_dst;
	char	*substr;

	substr = ft_substr(src, 0, len);
	if (!substr)
	{
		print_error(strerror(errno));
		free(*dst);
		return (FAIL);
	}
	new_dst = ft_strjoin(*dst, substr);
	free(*dst);
	free(substr);
	*dst = new_dst;
	if (!new_dst)
	{
		print_error(strerror(errno));
		return (FAIL);
	}
	return (SUCCESS);
}
