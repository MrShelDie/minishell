/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:21:17 by medric            #+#    #+#             */
/*   Updated: 2022/07/29 19:53:01 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "executer_private.h"
#include <stdlib.h>

// static char	*cut_key(const t_map *env_map, const char *str, size_t *i)
// {
// 	while (ft_isalnum(str[*i]) || str[*i] == '_')
// 		++(*i);
// 	return (ft_strldup(str, *i));
// }

// static int	append_expanded_dolar(
// 	const t_map *env_map, char **dst, char **src)
// {
// 	size_t		i;
// 	char		*new_substr;
// 	char		*key;
// 	const char	*value;

// 	i = 0;
// 	++(*src);
// 	key = cut_key(env_map, *src, &i);
// 	if (!key)
// 	{
// 		free(*dst);
// 		return (FAIL);
// 	}
// 	value = map_get(env_map, key);
// 	free(key);
// 	*src += i;
// 	if (!value)
// 		return (SUCCESS);
// 	new_substr = ft_strjoin(*dst, value);
// 	free(*dst);
// 	if (!new_substr)
// 		return (FAIL);
// 	*dst = new_substr;
// 	return (SUCCESS);
// }

// int	append_regular_str(char **dst, char **src)
// {
// 	size_t	i;
// 	char	*new_substr;
	
// 	i = 0;
// 	while ((*src)[i] && !((*src)[i] == '$'
// 			&& (ft_isalnum((*src)[i + 1]) || (*src)[i + 1] == '_')))
// 		++i;
// 	new_substr = ft_strjoin(*dst, ft_strldup(*src, i));
// 	free(*dst);
// 	if (!new_substr)
// 		return (FAIL);
// 	*dst = new_substr;
// 	*src += i;
// 	return (SUCCESS);
// }

static int	append_substr(char **dst, const char *src, size_t len)
{
	char	*new_dst;
	char	*substr;

	substr = ft_substr(src, 0, len);
	if (!substr)
	{
		free(*dst);
		return (FAIL);
	}
	new_dst = ft_strjoin(*dst, substr);
	free(*dst);
	free(substr);
	*dst = new_dst;
	if (!new_dst)
		return (FAIL);
	return (SUCCESS);
}

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

static int	append_regular_str(char **dst, char **src)
{
	size_t	i;
	
	i = 0;
	while ((*src)[i] && !((*src)[i] == '$'
 			&& (ft_isalnum((*src)[i + 1]) || (*src)[i + 1] == '_')))
		++i;
	if (!append_substr(dst, *src, i))
		return (FAIL);
	*src += i;
	return (SUCCESS);
}

int	replace_expanded_str(
	const t_map *env_map, char **str)
{
	char	*expanded;
	char	*str_copy;

	str_copy = *str;
	expanded = ft_strdup("");
	if (!expanded)
		return (FAIL);
	while (**str)
	{
		if (!append_regular_str(&expanded, str))
			return (FAIL);
		if (!**str)
			break ;
		if (!append_expanded_dolar(env_map, &expanded, str))
			return (FAIL);
	}
	free(str_copy);
	*str = expanded;
	return (SUCCESS);
}
