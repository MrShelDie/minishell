/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_expanded_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:42:17 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/06 18:45:03 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"

int	append_expanded_variable(
	const t_shell_data *shell_data, char **dst, char **src)
{
	const char	*variable_value;
	size_t		variable_length;

	++(*src);
	variable_value = get_variable_value(shell_data, *src);
	variable_length = get_variable_length(*src);
	*src += variable_length;
	if (!variable_value)
		return (SUCCESS);
	if (!append_substr(dst, variable_value, ft_strlen(variable_value)))
		return (FAIL);
	return (SUCCESS);
}

static int	append_expanded_double_quotes_str(
	const t_shell_data *shell_data, char **dst, char **src)
{
	size_t	i;

	i = 0;
	++(*src);
	while ((*src)[i] != '\"')
	{
		while ((*src)[i] != '\"' && !is_variable(*src + i))
			++i;
		if (!append_substr(dst, *src, i))
			return (FAIL);
		(*src) += i;
		if (**src == '$')
		{
			if (!append_expanded_variable(shell_data, dst, src))
				return (FAIL);
		}
		i = 0;
	}
	++(*src);
	return (SUCCESS);
}

static int	append_expanded_quotes_str(char **dst, char **src)
{
	size_t	i;

	i = 0;
	++(*src);
	while ((*src)[i] != '\'')
		++i;
	if (!append_substr(dst, *src, i))
		return (FAIL);
	(*src) += i + 1;
	return (SUCCESS);
}

int	append_expanded_str(
	const t_shell_data *shell_data, char **dst, char **src)
{
	if (**src == '\'' && !append_expanded_quotes_str(dst, src))
		return (FAIL);
	else if (**src == '\"'
		&& !append_expanded_double_quotes_str(shell_data, dst, src))
		return (FAIL);
	else if (
		is_variable(*src) && !append_expanded_variable(shell_data, dst, src))
		return (FAIL);
	return (SUCCESS);
}
