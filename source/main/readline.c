/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:19:56 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/10 01:07:29 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

/**
 * @brief Writes prompt string and reads user input.
 * 
 * @param shell_data A pointer to the structure in the field
 * 		of which the data entered by the user will be accumulated.
 * @return If EOF is read or a read error occurs, it returns 0,
 * 		in other cases it always returns 1.
 */
int	shell_readline(t_shell_data *shell_data)
{
	// TODO prompt string like in bash
	shell_data->user_input = readline("minishell> ");
	if (shell_data->user_input)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief Handler for reading heredoc.
 * 		Reads user input, makes variable substitutions,
 * 		writes the result to a temporary file.
 * 
 * @param shell_data A pointer to the structure in the field
 * 		of which the data entered by the user will be accumulated.
 * @return Returns a temporary file descriptor.
 * 		In case of an error, returns -1.
 */
int	shell_read_heredoc(t_shell_data *shell_data)
{
	// TODO
}

/**
 * @brief Adds accumulated user input to the history.
 * 
 * @param shell_data A pointer to a structure that contains
 * 		accumulated user input.
 */
void	shell_add_history(t_shell_data *shell_data)
{
	add_history(shell_data->user_input);
	free(shell_data->user_input);
	shell_data->user_input = NULL;
}
