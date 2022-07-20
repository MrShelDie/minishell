/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:51:13 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 18:56:45 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "minishell.h"
#include <limits.h>

int	ft_pwd(void)
{
	char	cmd[PATH_MAX];

	getcwd(cmd, PATH_MAX);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd("\n", 1);
	return (SUCCESS);
}
