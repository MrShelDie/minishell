/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:51:13 by medric            #+#    #+#             */
/*   Updated: 2022/07/31 21:07:52 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"
#include <limits.h>

int	ft_pwd(t_shell_data *data, char **argv)
{
	char	cmd[PATH_MAX];

	(void)data;
	(void)argv;
	getcwd(cmd, PATH_MAX);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd("\n", 1);
	return (SUCCESS);
}
