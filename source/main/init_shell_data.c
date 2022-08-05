/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:11:11 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/05 14:53:16 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "minishell_private.h"
#include "libft.h"
#include "shell_error.h"

static void	set_builtin_array(t_builtin *builtins)
{
	builtins[BUILTIN_CD] = ft_cd;
	builtins[BUILTIN_ECHO] = ft_echo;
	builtins[BUILTIN_ENV] = ft_env;
	builtins[BUILTIN_EXPORT] = ft_export;
	builtins[BUILTIN_PWD] = ft_pwd;
	builtins[BUILTIN_UNSET] = ft_unset;
}

static void	handle_shell_init_error(t_shell_data *shell_data)
{
	destroy_shell_data(shell_data);
	exit_with_error_msg(strerror(errno), EXIT_FAILURE);
}

void	init_shell_data(t_shell_data *shell_data, char *const *envp)
{
	ft_bzero(shell_data, sizeof(t_shell_data));
	shell_data->env_vector = vector_create_from_array(envp);
	shell_data->env_map = map_create();
	if (shell_data->env_map == FAIL
		|| shell_data->env_vector == FAIL
		|| parse_env_to_map(shell_data->env_map, envp) == FAIL
		|| increase_shlvl_in_map_and_vector(
			shell_data->env_map, shell_data->env_vector) == FAIL
	)
		handle_shell_init_error(shell_data);
	set_builtin_array(shell_data->builtins);
}
