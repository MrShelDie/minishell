/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:50:02 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/10 01:10:02 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell_data	*shell_data;

	if (argc != 1)
	{
		// TODO handle error
	}
	shell_data = shell_init(envp);
	if (!shell_data)
	{
		// TODO error handle
	}
	// TODO signal handler
	while (shell_readline(shell_data))
	{
		// TODO parse
		// TODO execute
		shell_add_history(shell_data);
	}
	return (0);
}
