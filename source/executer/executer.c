/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 17:36:57 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/builtin.h"
#include "../../include/minishell.h"
#include <stdio.h>

int	builtins(t_shell_data *shell_data, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd->data[i], "echo", 4) == 0)
	{
		i++;
		if (ft_echo(cmd->data, i) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "pwd", 3) == 0)
	{
		i++;
		if (ft_pwd() == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "env", 3) == 0)
	{
		i++;
		if (ft_env(shell_data->env_map->head) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "cd", 2) == 0)
	{
		i++;
		if (ft_cd(cmd->data, shell_data) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "unset", 5) == 0)
	{
		i++;
		if (ft_unset(cmd->data, shell_data) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "export", 6) == FAIL)
	{
		if (ft_export(cmd, shell_data) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	executer(t_shell_data *shell_data, t_cmd *cmd)
{
	if (!builtins(shell_data, cmd))
		return (FAIL);
	exit(1);
	return (SUCCESS);
}
