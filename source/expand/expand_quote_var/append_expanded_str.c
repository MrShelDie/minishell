/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_expanded_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:42:17 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/25 16:43:56 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_private.h"
#include <stdlib.h>

static char	*cut_key(const t_map *env_map, const char *str, size_t *i)
{
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		++(*i);
	return (ft_strldup(str, i));
}

static int	append_expanded_dolar(
	const t_map *env_map, char **dst, const char **src)
{
	size_t	i;
	char	*new_substr;
	char	*key;
	char	*value;

	i = 0;
	++(*src);
	key = cut_key(env_map, *src, &i);
	if (!key)
	{
		free(*dst);
		return (FAIL);
	}
	value = map_get(env_map, key);
	free(key);
	*src += i;
	if (!value)
		return (SUCCESS);
	new_substr = ft_strjoin(*dst, value);
	free(*dst);
	if (!new_substr)
		return (FAIL);
	*dst = new_substr;
	return (SUCCESS);
}

static int	append_expanded_double_quotes_str(
	const t_map *env_map, char **dst, const char **src)
{
	size_t	i;

	i = 0;
	++(*src);
	while ((*src)[i] != '\"')
	{
		while ((*src)[i] != '\"' && !((*src)[i] == '$' && (*src)[i + 1]))
			++i;
		if (!append_regular_str(dst, src))
			return (FAIL);
		if (**src == '$')
		{
			if (!append_expanded_dolar(env_map, dst, src))
				return (FAIL);
		}
		i = 0;
	}
	++(*src);
	return (SUCCESS);
}

static int	append_expanded_quotes_str(char **dst, const char **src)
{
	size_t	i;
	char	*new_substr;

	i = 0;
	++(*src);
	while ((*src)[i] != '\'')
		++i;
	new_substr = ft_strjoin(*dst, ft_strldup(*src, i));
	free(*dst);
	if (!new_substr)
		return (FAIL);
	*dst = new_substr;
	(*src) += i + 1;
	return (SUCCESS);
}

int	append_expanded_str(
	const t_map *env_map, char **dst, const char **src)
{
	if (**src == '\'' && !append_expanded_quotes_str(dst, src))
		return (FAIL);
	else if (**src == '\"' && !append_expanded_double_quotes_str(env_map, dst, src))
		return (FAIL);
	else if (**src == '$' && *(*src + 1) && !append_expanded_dolar(env_map, dst, src))
		return (FAIL);
	return (SUCCESS);
}
