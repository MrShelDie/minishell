/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/11 19:33:55 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../builtin/builtins.h"
#include "minishell.h"
#include <stdio.h>

// int	check_builtin(const char *s)
// {
// 	if (ft_strncmp(s, "echo", 4) == 0)
// 		return (1);
// 	else if (ft_strncmp(s, "pwd", 3) == 0)
// 		return (1);
// 	else
// 		return (0);
// }

int	builtins(t_shell_data *shell_data, t_cmd *cmd)
{
	int	i;

	i = 0;
	(void) *shell_data;
	if (ft_strncmp(cmd->data[i], "echo", 4) == 0)
	{
		i++;
		if (ft_echo(cmd->data, i) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

int	executer(t_shell_data *shell_data, t_cmd *cmd)
{
	// pid_t	pid;

	if (!builtins(shell_data, cmd))
		return (FAIL);
	return (SUCCESS);
}
