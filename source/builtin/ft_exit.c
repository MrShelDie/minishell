/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:47:05 by medric            #+#    #+#             */
/*   Updated: 2022/08/05 18:01:32 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int	ft_exit(t_shell_data *shell_data, t_vector *cmd)
{
	unsigned int	exit_status;
	size_t			i;

	i = 0;
	while (ft_isdigit(cmd->data[1][i]))
	{
		if (ft_isalpha(cmd->data[1][i]) == 1)
		{
			i = 0;
			break ;
		}
		i++;
	}	
	if (!cmd->data[2] && i > 0)
	{
		exit_status = ft_atou(cmd->data[1]);
		ft_putstr_fd("exit\n", 1);
		shell_data->is_run = false;
		return (exit_status);
	}
	else
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (1);
	}
}
