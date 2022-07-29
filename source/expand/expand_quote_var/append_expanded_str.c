/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_expanded_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:42:17 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/29 15:38:06 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"
#include <stdlib.h>

static char	*cut_key(char *str, size_t *i)
{
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		++(*i);
	return (ft_substr(str, 0, *i));
}

static int	append_expanded_dolar(
	const t_map *env_map, char **dst, char **src)
{
	size_t		i;
	char		*key;
	const char	*value;

	i = 0;
	++(*src);
	key = cut_key(*src, &i);
	if (!key)
	{
		free(*dst);
		return (FAIL);
	}
	value = map_get(env_map, key);
	free(key);
	if (!value)
	{
		*src += i;
		return (SUCCESS);
	}
	if (!append_substr(dst, value, ft_strlen(value)))
		return (FAIL);
	*src += i;
	return (SUCCESS);
}

static int	append_expanded_double_quotes_str(
	const t_map *env_map, char **dst, char **src)
{
	size_t	i;

	i = 0;
	++(*src);
	while ((*src)[i] != '\"')
	{
		while ((*src)[i] != '\"' && !((*src)[i] == '$'
				&& (ft_isalnum((*src)[i + 1]) || (*src)[i + 1] == '_')))
			++i;
		if (!append_substr(dst, *src, i))
			return (FAIL);
		(*src) += i;
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
	const t_map *env_map, char **dst, char **src)
{
	if (**src == '\'' && !append_expanded_quotes_str(dst, src))
		return (FAIL);
	else if (**src == '\"'
		&& !append_expanded_double_quotes_str(env_map, dst, src))
		return (FAIL);
	else if (**src == '$' && (ft_isalnum((*src)[1]) || (*src)[1] == '_')
		&& !append_expanded_dolar(env_map, dst, src))
		return (FAIL);
	return (SUCCESS);
}
