/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:50:02 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/11 18:45:08 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_shell_data	*shell_data;

// 	if (argc != 1)
// 	{
// 		// TODO handle error
// 	}
// 	shell_data = shell_init(envp);
// 	if (!shell_data)
// 	{
// 		// TODO error handle
// 	}
// 	// TODO signal handler
// 	while (1)
// 	{
// 		// TODO readline
// 		// TODO execute
// 		// TODO add_history
// 	}
// 	return (0);
// }

#include "lexer.h"
#include <assert.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void	print_token(void *token)
{
	printf("ID: %d\tVALUE: %s\n", ((t_token *)token)->id, ((t_token *)token)->value);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell_data	*shell_data;
	t_list			*token_list;
	char			*input;

	(void)argc;
	(void)argv;
	shell_data = shell_init(envp);
	assert(shell_data);
	while (1)
	{
		input = readline("> ");
		token_list = get_token_list(input);
		free(input);
		ft_lstiter(token_list, print_token);
	}
	return (0);
}
