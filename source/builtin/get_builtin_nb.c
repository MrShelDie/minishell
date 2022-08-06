/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin_nb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:43:33 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/06 16:13:01 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin_nb	get_builtin_nb(const char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (BUILTIN_CD);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (BUILTIN_ECHO);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (BUILTIN_ENV);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (BUILTIN_EXPORT);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (BUILTIN_EXIT);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (BUILTIN_PWD);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (BUILTIN_UNSET);
	return (BUILTIN_NONE);
}
