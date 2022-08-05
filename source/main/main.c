/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:50:02 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/05 14:53:09 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell_private.h"
#include "parser.h"
#include "executer.h"
#include "shell_error.h"
#include "shell_signal.h"

bool	check_key_in_string(const char *key, const char *string);

int	execute_user_input(t_shell_data *shell_data, char *user_input)
{
	t_parsed_data	parsed_data;
	int				exit_status;

	if (set_ignore_sigint() == FAIL)
		return (EXIT_FAILURE);
	exit_status = EXIT_FAILURE;
	ft_bzero(&parsed_data, sizeof(t_parsed_data));
	if (parse_user_input(&parsed_data, user_input) == SUCCESS)
		exit_status = execute_parsed_line(shell_data, &parsed_data);
	destroy_parsed_data(&parsed_data);
	if (set_interactive_mode_signals() == FAIL)
		return (EXIT_FAILURE);
	return (exit_status);
}

static char	*shell_readline(void)
{
	char	*user_input;

	user_input = readline("minishell> ");
	if (!user_input)
		return (NULL);
	if (!ft_is_space_str(user_input))
		add_history(user_input);
	return (user_input);
}

static int	shell_loop(t_shell_data	*shell_data)
{
	char	*user_input;

	if (set_interactive_mode_signals() == FAIL)
		return (EXIT_FAILURE);
	user_input = shell_readline();
	while (user_input)
	{
		if (!ft_is_space_str(user_input))
			shell_data->exit_status = execute_user_input(
					shell_data, user_input);
		free(user_input);
		user_input = shell_readline();
	}
	return (shell_data->exit_status);
}

static void	check_argc(int argc)
{
	if (argc > 1)
		exit_with_error_msg(
			"the number of arguments is not zero", EXIT_FAILURE);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell_data	shell_data;
	int				exit_status;

	(void)argv;
	check_argc(argc);
	disable_display_control_symbols();
	init_shell_data(&shell_data, envp);
	exit_status = shell_loop(&shell_data);
	destroy_shell_data(&shell_data);
	rl_clear_history();
	return (exit_status);
}
