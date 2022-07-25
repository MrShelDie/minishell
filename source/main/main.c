/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:50:02 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/24 14:48:27 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executer.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 * @brief Checks if the string consists of only whitespace characters.
 * 
 * @param str The string to be checked.
 * @return 1 if the string consists of only whitespace characters,
 * 		   0 if not.
 */
static int	is_space_string(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		++str;
	}
	return (1);
}

static bool	check_closing_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			++str;
			while (*str && *str != '\'')
				++str;
			if (!*str)
				return (false);
		}
		else if (*str == '\"')
		{
			++str;
			while (*str && *str != '\"')
				++str;
			if (!*str)
				return (false);
		}
		++str;
	}
	return (true);
}

/**
 * @brief Writes the prompt string, reads user input and adds it to the history
 * 		if if at least one non-whitespace character was entered.
 * 
 * @return The string entered by the user.
 * 		If EOF is read or a read error occurs, it returns NULL,
 */
static char	*shell_readline(void)
{
	char	*user_input;

	// TODO prompt string like in bash
	user_input = readline("minishell> ");
	if (user_input && !is_space_string(user_input))
		add_history(user_input);
	return (user_input);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell_data	shell_data;
	t_parsed_data	parsed_data;
	t_token_list	*token_list;
	char			*user_input;

	(void)argc;
	// TODO handle argc and argv
	if (!shell_init(&shell_data, argv, envp))
	{
		// TODO error handler
		return (0);
	}
	while (1)
	{
		user_input = shell_readline();
		if (!user_input)
		{
			// TODO error handler
			return (0);
		}
		if (user_input[0] == '\0')
			continue ;
		if (!check_closing_quotes(user_input))
		{
			printf(SYNTAX_ERR_MSG);
			printf("'newline\n'");
			continue ;
		}
		token_list = get_token_list(user_input);
		if (!token_list)
		{
			// TODO error handler
			shell_destroy(&shell_data);
			return (0);
		}
		init_parsed_data(&parsed_data);
		if (parse(&parsed_data, token_list))
			executer(&shell_data, &parsed_data);
		destroy_parsed_data(&parsed_data);
		ft_lstclear(&token_list, destroy_token);
	}
	clear_history();
	return (0);
}
