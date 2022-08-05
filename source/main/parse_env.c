/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:05:54 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/05 14:53:22 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell_private.h"
#include "libft.h"

static char	**split_env(const char *env_line)
{
	char	**env_pair;
	char	*equal_symbol;
	size_t	key_len;
	size_t	value_len;

	equal_symbol = ft_strchr(env_line, '=');
	key_len = equal_symbol - env_line;
	value_len = ft_strrchr(env_line, '\0') - equal_symbol - 1;
	env_pair = ft_calloc(2, sizeof(char *));
	if (!env_pair)
		return (NULL);
	env_pair[0] = ft_substr(env_line, 0, key_len);
	env_pair[1] = ft_substr(env_line, key_len + 1, value_len);
	if (!env_pair[0] || !env_pair[1])
	{
		free(env_pair[0]);
		free(env_pair[1]);
		free(env_pair);
		return (NULL);
	}
	return (env_pair);
}

static int	parse_env_line_to_map(t_map *map, const char *env_line)
{
	char	**env_pair;
	int		map_add_status;

	env_pair = split_env(env_line);
	if (!env_pair)
		return (FAIL);
	map_add_status = map_add(map, env_pair[0], env_pair[1]);
	free(env_pair[0]);
	free(env_pair[1]);
	return (map_add_status);
}

/**
 * @brief Parses an array of environment variables into a map.
 * 
 * @param map Pointer to the map.
 * @param envp Array of environment variables.
 * @return If successful, the value 1 is returned.
 * 		   In case of a memory allocation error, the value 0 is returned.
 */
int	parse_env_to_map(t_map *map, char *const *envp)
{
	while (*envp)
	{
		if (ft_strchr(*envp, '=') && !parse_env_line_to_map(map, *envp))
			return (FAIL);
		++envp;
	}
	return (SUCCESS);
}
