/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:50:02 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/09 21:32:33 by gannemar         ###   ########.fr       */
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
	while (1)
	{
		// TODO readline
		// TODO execute
		// TODO add_history
	}
	return (0);
}
