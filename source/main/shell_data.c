/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:11:11 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/31 22:19:06 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"
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

void	set_builtin_array(t_builtin *builtins)
{
	builtins[CD] = ft_cd;
	builtins[ECHO] = ft_echo;
	builtins[ENV] = ft_env;
	builtins[EXPORT] = ft_export;
	builtins[PWD] = ft_pwd;
	builtins[UNSET] = ft_unset;
}

/**
 * @brief Initializes the general data structure of the program (shell_data).
 * 
 * @param shell_data Pointer to the shell_data structure.
 * @param argv Pointer to an array of program arguments.
 * @param envp Pointer to an array of environment variables.
 * @return If successful, pointer to the an initialized structure shell_data
 * 		is returned.
 * 		   In case of a memory allocation error or if a null pointer is passed
 * 		to the function, a null value is returned.
 */
t_shell_data	*shell_init(t_shell_data *shell_data, char *const *argv,
	char *const *envp)
{
	if (!shell_data)
		return (NULL);
	ft_bzero(shell_data, sizeof(t_shell_data));
	shell_data->env_vector = vector_create_from_array(envp);
	shell_data->env_map = map_create();
	if (!shell_data->env_vector
		|| !shell_data->env_map
		|| !parse_env_to_map(shell_data->env_map, envp))
	{
		shell_destroy(shell_data);
		return (NULL);
	}
	shell_data->program_name = argv[0];
	set_builtin_array(shell_data->builtins);
	return (shell_data);
}

/**
 * @brief Frees up the memory allocated for the general data of the program.
 * 
 * @param shell_data Pointer to the general data structure shell_data.
 */
void	shell_destroy(t_shell_data *shell_data)
{
	if (!shell_data)
		return ;
	if (shell_data->env_map)
		map_destroy(shell_data->env_map);
	if (shell_data->env_vector)
		vector_destroy(shell_data->env_vector);
	ft_bzero(shell_data, sizeof(t_shell_data));
}
