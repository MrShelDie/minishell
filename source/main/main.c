/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:50:02 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/11 19:35:55 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_strcpyl(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < (size - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell_data	*shell_data;
	t_cmd			*cmd;
	int				size;
	int				len;

	size = 1;
	len = 0;
	if (argc != 1)
	{
		// TODO handle error
	}
	while (argv[size])
		size++;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->data = (char **)malloc(sizeof(char *) * size);
	size = 1;
	while (argv[size])
	{
		cmd->data[len] = (char *)malloc(sizeof(char) * (ft_strlen(argv[size]) + 1));
		ft_strcpyl(cmd->data[len], argv[size], (ft_strlen(argv[size]) + 1));
		size++;
		len++;
	}
	shell_data = shell_init(envp);
	// while (cmd)
	// {
	// 	printf(" %s ", cmd->data);
	// 	cmd = cmd->next;
	// }
	// while (shell_data->env_map->head)
	// {
	// 	if (ft_strncmp(shell_data->env_map->head->key, "PWD", 3) == 0)
	// 	{
	// 		printf("%s\n", shell_data->env_map->head->value);
	// 		break ;
	// 	}
	// 	shell_data->env_map->head = shell_data->env_map->head->next;
	// }
	// if (!shell_data)
	// {
	// 	// TODO error handle
	// }
	// // TODO signal handler
	while (1)
	{
		if (executer(shell_data, cmd) == FAIL || signal)
		break ;
	}
	return (0);
}
