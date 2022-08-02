/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin_nb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:43:33 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/02 14:21:05 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin_nb	get_builtin_nb(const char *cmd)
{
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (BUILTIN_CD);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (BUILTIN_ECHO);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (BUILTIN_ENV);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (BUILTIN_EXPORT);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (BUILTIN_PWD);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (BUILTIN_UNSET);
	return (BUILTIN_NONE);
}