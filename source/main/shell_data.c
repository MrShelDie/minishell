/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:11:11 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/09 21:37:24 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

/**
 * @brief Splits a string of the form "KEY=VALUE" into an array of the form
 * 		  {"KEY", "VALUE"}.
 * 		  The function allocates memory for KEY and VALUE in the array.
 * 
 * @param env A string of the form "KEY=VALUE"
 * @param env_pair Array where the result will be written.
 * @return If successful, the value 1 is returned.
 * 		   In case of a memory allocation error, the value 0 is returned.
 */
static int	split_env(const char *env, char *env_pair[2])
{
	size_t	i;

	i = 0;
	while (env[i] != '=')
		++i;
	env_pair[0] = malloc(sizeof(char) * (i + 1));
	if (!env_pair[0])
		return (FAIL);
	ft_strlcpy(env_pair[0], env, i + 1);
	env += i + 1;
	i = 0;
	while (env[i])
		i++;
	env_pair[1] = malloc(sizeof(char) * (i + 1));
	if (!env_pair[1])
	{
		free(env_pair[0]);
		return (FAIL);
	}
	ft_strlcpy(env_pair[1], env, i + 1);
	return (SUCCESS);
}

/**
 * @brief Parses an array of environment variables into a map.
 * 
 * @param map Pointer to the map.
 * @param envp Array of environment variables.
 * @return If successful, the value 1 is returned.
 * 		   In case of a memory allocation error, the value 0 is returned.
 */
static int	parse_env_to_map(t_map *map, char *const *envp)
{
	char	*env_pair[2];
	int		map_add_status;

	while (*envp)
	{
		if (!split_env(*envp, env_pair))
			return (FAIL);
		map_add_status = map_add(map, env_pair[0], env_pair[1]);
		free(env_pair[0]);
		free(env_pair[1]);
		if (!map_add_status)
			return (FAIL);
		++envp;
	}
	return (SUCCESS);
}

/**
 * @brief Creates and initializes the general data structure of the program.
 * 
 * @param envp Pointer to an array of environment variables.
 * @return If successful, pointer to the created structure is returned.
 * 		   In case of a memory allocation error, the NULL value is returned.
 */
t_shell_data	*shell_init(char *const *envp)
{
	t_shell_data	*shell_data;

	shell_data = (t_shell_data *)malloc(sizeof(t_shell_data));
	if (!shell_data)
		return (NULL);
	ft_memset(shell_data, 0, sizeof(t_shell_data));
	shell_data->env_vector = vector_create_copy(envp);
	shell_data->env_map = map_create();
	if (!shell_data->env_vector
		|| !shell_data->env_map
		|| !parse_env_to_map(shell_data->env_map, envp))
	{
		shell_destroy(shell_data);
		return (NULL);
	}
	shell_data->user_input = NULL;
	return (shell_data);
}

/**
 * @brief Frees up the memory allocated for the general data of the program.
 * 
 * @param shell_data Pointer to the general data structure.
 */
void	shell_destroy(t_shell_data *shell_data)
{
	if (!shell_data)
		return ;
	if (shell_data->env_map)
		map_destroy(shell_data->env_map);
	if (shell_data->env_vector)
		vector_destroy(shell_data->env_vector);
	if (shell_data->user_input)
		free(shell_data->user_input);
	ft_memset(shell_data, 0, sizeof(t_shell_data));
	free(shell_data);
}
