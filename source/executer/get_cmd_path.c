/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:34:37 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/05 13:07:33 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd_paths(t_map *env)
{
	char	*path;
	char	**paths;

	path = (char *)map_get(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	return (paths);
}

char	*get_cmd(char **paths, const char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		ft_strdel(&tmp);
		if (access(command, 0) == 0)
			return (command);
		ft_strdel(&command);
		paths++;
	}
	return (ft_strdup(cmd));
}
