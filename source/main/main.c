/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:50:02 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/19 17:20:22 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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


// -------------------------------------TEST-BEGIN------------------------------------

void print_redir(void *redir)
{
	const char	*id;

	switch (((t_redir *)redir)->id)
	{
	case REDIR_IN: id = "<";
		break;
	case REDIR_OUT: id = ">";
		break;
	case REDIR_OUT_APPEND: id = ">>";
		break;
	case REDIR_HEREDOC: id = "<<";
	}
	printf("[%s %s] ", id, ((t_redir *)redir)->value);
}

void print_cmd(void *cmd)
{
	printf("\t\tCMD:\n");
	printf("\t\t\tIs subshell:\t%s\n", ((t_cmd *)cmd)->is_subshell ? "true" : "false");
	printf("\t\t\tArgv:\t\t");
	for (size_t i = 0; i < ((t_cmd *)cmd)->argv->length; i++)
		printf("[%s] ", ((t_cmd *)cmd)->argv->data[i]);
	printf("\n");
	printf("\t\t\tRedir:\t\t");
	ft_lstiter(((t_cmd *)cmd)->redir_list, print_redir);
	printf("\n");
}

void print_cmd_list(void *cmd_list)
{
	printf("\tCMD LIST:\n");
	ft_lstiter(cmd_list , print_cmd);
}

void print_operator(void *op)
{
	if (*(t_operator *)op == OP_AND)
		printf("\tAND\n");
	else if (*(t_operator *)op == OP_OR)
		printf("\tOR\n");
	else
		printf("\tNEW_LINE\n");
}

void print_parsed_data(t_parsed_data *parsed_data)
{
	printf("-----------------------------------------------------------------\n");
	printf("PIPE GROUP LIST:\n");
	ft_lstiter(parsed_data->pipe_group_list, print_cmd_list);
	printf("OPERATOR LIST:\n");
	ft_lstiter(parsed_data->operator_list, print_operator);
	printf("-----------------------------------------------------------------\n");
}

// -------------------------------------TEST-END------------------------------------

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
	// TODO signal handler
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
		token_list = get_token_list(user_input);
		if (!token_list)
		{
			// TODO error handler
			shell_destroy(&shell_data);
			return (0);
		}
		init_parsed_data(&parsed_data);
		
		if (parse(&parsed_data, token_list))
			print_parsed_data(&parsed_data);
		// TODO executer

		destroy_parsed_data(&parsed_data);
		ft_lstclear(&token_list, destroy_token);

		// ! NEED FIX
		clear_history();
	}
	return (0);
}
