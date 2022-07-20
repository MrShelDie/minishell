/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:51:13 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 17:40:24 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/builtins.h"
#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	cmd[PATH_MAX];

	getcwd(cmd, PATH_MAX);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, 1);
		return (SUCCESS);
	}
	else
		return (FAIL);
}
