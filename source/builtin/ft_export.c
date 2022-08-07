/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 22:58:22 by medric            #+#    #+#             */
/*   Updated: 2022/08/07 21:32:09 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"

static void	putstr(int len, char **map_buff)
{
	int		i;
	char	**strings;

	i = -1;
	while (++i < len)
	{
		if (ft_strchr(map_buff[i], '='))
		{
			strings = split_env(map_buff[i]);
			printf("declare -x %s='%s'\n", strings[0], strings[1]);
			free(strings[0]);
			free(strings[1]);
			free(strings);
		}
		else
			printf("declare -x %s\n", map_buff[i]);
	}
}

static int	print_sort_env(t_vector *map)
{
	char	**map_buff;
	int		err;

	err = 0;
	map_buff = NULL;
	map_buff = create_buff(map_buff, map, &err);
	if (err == 1)
	{
		delete_buff(map_buff, map->length);
		return (FAIL);
	}
	map_buff = sort_buff(map_buff, map->length);
	putstr((int)map->length, map_buff);
	delete_buff(map_buff, map->length);
	return (SUCCESS);
}

static int	vector_add_or_replace(t_shell_data *shell_data, char *s, char *tmp)
{
	size_t		i;
	t_vector	*vector;
	char		**words;

	i = -1;
	vector = shell_data->env_vector;
	while (++i < vector->length)
	{
		words = split_env(vector->data[i]);
		if (!words)
			return (FAIL);
		if (ft_strncmp(vector->data[i], s, ft_strlen(s)) == 0 && tmp == NULL)
			return (SUCCESS);
		else if (tmp != NULL
			&& ft_strncmp(words[0], tmp, ft_strlen(words[0]) + 1) == 0)
		{
			vector_insert_at(vector, vector->data[i], i);
			return (SUCCESS);
		}
		delete_buff(words, 2);
	}
	if (!vector_add(vector, s))
		return (FAIL);
	return (SUCCESS);
}

int	add_data(t_shell_data *data, t_vector *cmd)
{
	char	**tmp;
	int		i;

	i = 1;
	tmp = NULL;
	if (ft_searchr(cmd->data[i], '=') == 0)
	{
		if (vector_add_or_replace(data, cmd->data[i], NULL) == FAIL)
			return (FAIL);
		return (SUCCESS);
	}
	tmp = ft_split(cmd->data[i], '=');
	if (!tmp)
		return (FAIL);
	if (map_add(data->env_map, tmp[0], tmp[1]) == FAIL)
		return (FAIL);
	if (vector_add_or_replace(data, cmd->data[i], tmp[0]) == FAIL)
		return (FAIL);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (SUCCESS);
}

int	ft_export(t_shell_data *data, t_vector *cmd)
{
	if (cmd->length < 2)
	{
		if (print_sort_env(data->env_vector) == FAIL)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (add_data(data, cmd) == FAIL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
