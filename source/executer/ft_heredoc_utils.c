/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:21:17 by medric            #+#    #+#             */
/*   Updated: 2022/07/28 20:22:19 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "minishell.h"
#include "parser.h"
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "get_next_line.h"

/**
 * @brief In this function we delete buffers in our heredoc function, which we create
 * @param av buffer, which we want to destroy
 */
void	delete_buff_here(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	av = NULL;
}

static char	*cut_key(const t_map *env_map, const char *str, size_t *i)
{
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		++(*i);
	return (ft_strldup(str, *i));
}

static int	append_expanded_dolar(
	const t_map *env_map, char **dst, char **src)
{
	size_t		i;
	char		*new_substr;
	char		*key;
	const char	*value;

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

int	append_regular_str(char **dst, char **src)
{
	size_t	i;
	char	*new_substr;
	
	i = 0;
	while ((*src)[i] && !((*src)[i] == '$'
			&& (ft_isalnum((*src)[i + 1]) || (*src)[i + 1] == '_')))
		++i;
	new_substr = ft_strjoin(*dst, ft_strldup(*src, i));
	free(*dst);
	if (!new_substr)
		return (FAIL);
	*dst = new_substr;
	*src += i;
	return (SUCCESS);
}

int	replace_with_expanded_str(
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
