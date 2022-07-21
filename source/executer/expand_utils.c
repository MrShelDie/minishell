/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:49:42 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/21 20:38:56 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_expanded_dolar(char **dst, const char **src)
{
	// TODO
}

static int	append_expanded_double_quotes_str(char **dst, const char **src)
{
	// TODO
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

int	append_expanded_str(char **dst, const char **src)
{
	if (**src == '\'' && !append_expanded_quotes_str(dst, src))
		return (FAIL);
	else if (**src == '\"' && !append_expanded_double_quotes_str(dst, src))
		return (FAIL);
	else if (**src == '$' && !append_expanded_dolar(dst, src))
		return (FAIL);
	return (SUCCESS);
}

int	append_regular_str(char **dst, const char **src)
{
	size_t	i;
	char	*new_substr;
	
	while ((*src)[i] && (*src)[i] != '\'' && (*src)[i] != '\"'
		&& !((*src)[i] == '$' && (*src)[i + 1]))
		++i;
	new_substr = ft_strjoin(*dst, ft_strldup(*src, i));
	free(*dst);
	if (!new_substr)
		return (FAIL);
	*dst = new_substr;
	if ((*src)[i])
		(*src) += i + 1;
	else
		(*src) += i;
	return (SUCCESS);
}
