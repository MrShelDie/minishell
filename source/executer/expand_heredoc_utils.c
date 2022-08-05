/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:21:17 by medric            #+#    #+#             */
/*   Updated: 2022/08/05 16:20:45 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expand.h"
#include "minishell.h"
#include "executer_private.h"

#include <errno.h>
#include <string.h>
#include <stdlib.h>

static int	append_substr(char **dst, const char *src, size_t len)
{
	char	*new_dst;
	char	*substr;

	substr = ft_substr(src, 0, len);
	if (!substr)
	{
		free(*dst);
		print_error(strerror(errno));
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

static int	append_regular_str(char **dst, char **src)
{
	size_t	i;

	i = 0;
	while ((*src)[i] && !is_variable(*src + i))
		++i;
	if (!append_substr(dst, *src, i))
		return (FAIL);
	*src += i;
	return (SUCCESS);
}

int	replace_with_expanded_variables(
	const t_shell_data *shell_data, char **str)
{
	char	*expanded;
	char	*str_copy;

	str_copy = *str;
	expanded = ft_strdup("");
	if (!expanded)
	{
		print_error(strerror(errno));
		return (FAIL);
	}
	while (**str)
	{
		if (!append_regular_str(&expanded, str))
			return (FAIL);
		if (!**str)
			break ;
		if (!append_expanded_variable(shell_data, &expanded, str))
			return (FAIL);
	}
	free(str_copy);
	*str = expanded;
	return (SUCCESS);
}
