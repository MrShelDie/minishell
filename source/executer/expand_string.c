/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:02:46 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/21 20:33:30 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Checks for the need to expand string.
 * 
 * @param str The string that will be checked.
 * @return If it is necessary to expand the string returns true,
 * 	otherwise returns false.
 */
static bool	check_substitutions(const char *str)
{
	while (*str && *str != '\'' && *str != '\"' && !(*str == "$" && *(str + 1)))
		++str;
	if (*str)
		return (true);
	return (false);
}

/**
 * @brief Checks that all quotes are closed.
 * 
 * @param str The string that will be checked.
 * @return If all quotes are closed returns true, otherwise returns false.
 */
static bool	check_closing_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			++str;
			while (*str && *str != '\'')
				++str;
			if (!*str)
				return (false);
		}
		else if (*str == '\"')
		{
			++str;
			while (*str && *str != '\"')
				++str;
			if (!*str)
				return (false);
		}
		++str;
	}
	return (true);
}

static char	*get_expanded_str(const t_shell_data *shell_data, const char *str)
{
	char	*expanded;

	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (*str)
	{
		if (!append_regular_str(&expanded, &str)
			|| !append_expanded_str(&expanded, &str)
		)
			return (NULL);
	}
	return (expanded);
}

/**
 * @brief Modifies the string, if necessary, by opening quotes
 * 	and replacing environment variables.
 * 
 * @param shell_data General shell data.
 * @param str The string that will be expanded.
 * @return In case of success returns 1.
 * 	In case of memory allocation or expansion error returns 0.
 */
int	expand_string(const t_shell_data *shell_data, char **str)
{
	char	*expanded;

	if (!check_substitutions(*str))
		return (SUCCESS);
	if (!check_closing_quotes(*str))
	{
		printf(SYNTAX_ERR_MSG);
		printf("'newline\n'");
		return (FAIL);
	}
	expanded = get_expanded_str(shell_data, *str);
	if (!expanded)
		return (FAIL);
	free(*str);
	(*str) = expanded;
	return (SUCCESS);
}
