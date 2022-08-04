/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_expanded_str_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:46:00 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 15:51:13 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "../expand_private.h"
#include "shell_error.h"

size_t	get_variable_length(const char *str)
{
	size_t	i;

	if (str[0] == '?')
		return (1);
	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		++i;
	return (i);
}

static char	*cut_variable_name(const char *str)
{
	size_t	i;
	char	*variable_name;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		++(i);
	variable_name = ft_substr(str, 0, i);
	if (!variable_name)
		print_error(strerror(errno));
	return (variable_name);
}

static char	*get_variable_value_by_exit_status(const t_shell_data *shell_data)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(shell_data->exit_status);
	if (!exit_status_str)
		print_error(strerror(errno));
	return (exit_status_str);
}

static const char	*get_variable_value_by_name(t_map *env_map, const char *str)
{
	char		*variable_name;
	const char	*variable_value;

	variable_name = cut_variable_name(str);
	if (!variable_name)
		return (NULL);
	variable_value = map_get(env_map, variable_name);
	free(variable_name);
	return (variable_value);
}

const char	*get_variable_value(const t_shell_data *shell_data, const char *str)
{
	if (str[0] == '?')
		return (get_variable_value_by_exit_status(shell_data));
	return (get_variable_value_by_name(shell_data->env_map, str));
}
