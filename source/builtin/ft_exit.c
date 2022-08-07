/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:47:05 by medric            #+#    #+#             */
/*   Updated: 2022/08/07 18:39:51 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static int check_exit_arg(char *data)
{
	size_t			i;

	i = 0;
	if (ft_isalpha(data[i]) == 1)
	{
		ft_putstr_fd("exit: Illegal number:", 2);
		ft_putstr_fd(data, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	while (ft_isdigit(data[i]) == 1)
	{
		if (ft_isalpha(data[i + 1]) == 1)
		{
			ft_putstr_fd("exit: Illegal number:", 2);
			ft_putstr_fd(data, 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_exit(t_shell_data *shell_data, t_vector *cmd)
{
	unsigned int	exit_status;

	if (cmd->length <= 2)
	{
		if (cmd->length == 2)
		{
			if (check_exit_arg(cmd->data[1]) == 0)
				exit_status = ft_atou(cmd->data[1]);
			else
				return (1);
		}
		else
			exit_status = 0;
		ft_putstr_fd("exit\n", 2);
		shell_data->is_run = false;
	}
	return (exit_status);
}
