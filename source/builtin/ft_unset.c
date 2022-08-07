/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:59:03 by medric            #+#    #+#             */
/*   Updated: 2022/08/07 23:03:13 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"
#include <stdlib.h>

static char	*get_key_and_value(const char *key, const char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

int	ft_unset(t_shell_data *data, t_vector *cmd)
{	
	char		*key_and_value;
	const char	*value;
	int			exit_status;

	exit_status = EXIT_SUCCESS;
	key_and_value = NULL;
	value = map_get(data->env_map, cmd->data[1]);
	if (!value)
	{
		if (vector_delete(data->env_vector, cmd->data[1]) == FAIL)
			exit_status = EXIT_FAILURE;
	}
	else
	{
		key_and_value = get_key_and_value(cmd->data[1], value);
		if (!key_and_value)
			exit_status = EXIT_FAILURE;
	}
	if (vector_delete(data->env_vector, key_and_value) == FAIL)
		exit_status = EXIT_FAILURE;
	free(key_and_value);
	map_delete(data->env_map, cmd->data[1]);
	return (exit_status);
}
