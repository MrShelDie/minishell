/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pipe_group.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:54:19 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/21 15:48:02 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/**
 * @brief Modifies the data contained in the redirect list
 * 	by opening quotes and replacing environment variables.
 * 
 * @param shell_data General shell data.
 * @param redir_list A list of redirects, each element of which consists
 * 	of a redirect type and a value (the file name in the case of a regular
 * 	redirect or a stop word in the case of heredoc)
 * @return In case of success returns 1.
 * 	In case of memory allocation or expansion error returns 0.
 */
static int	expand_redir_list(const t_shell_data *shell_data, t_redir_list *redir_list)
{
	while (redir_list)
	{
		if (!expand_string(&((t_redir *)redir_list->content)->value))
			return (FAIL);
	}
	return (SUCCESS);
}

/**
 * @brief Modifies the data contained in the argument vector
 * 	by opening quotes and replacing environment variables.
 * 
 * @param shell_data General shell data.
 * @param argv A vector of arguments, the first
 * 	element of which is the name of the command.
 * @return In case of success returns 1.
 * 	In case of memory allocation or expansion error returns 0.
 */
static int	expand_argv(const t_shell_data *shell_data, t_vector *argv)
{
	size_t	i;

	i = -1;
	while (++i < argv->data)
	{
		if (!expand_string(&argv->data[i]))
			return (FAIL);
	}
	return (SUCCESS);
}

/**
 * @brief Modifies the data contained in the command structure
 * 	by opening quotes and replacing environment variables.
 * 
 * @param shell_data General shell data.
 * @param cmd The structure of a parsed simple command.
 * @return In case of success returns 1.
 * 	In case of memory allocation or expansion error returns 0.
 */
static int	expand_cmd(const t_shell_data *shell_data, t_cmd *cmd)
{
	if (!expand_argv(shell_data, cmd->argv)
		|| !expand_redir_list(shell_data, cmd->redir_list)
	)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief Modifies the data contained in the list of commands
 * 	by opening quotes and substituting environment variables.
 * 
 * @param shell_data General shell data.
 * @param cmd_list A list of parsed commands that were separated
 * 	by the '|' character in the line entered by the user.
 * @return In case of success returns 1.
 * 	In case of memory allocation or expansion error returns 0.
 */
static int	expand_pipe_group(const t_shell_data *shell_data, t_cmd_list *cmd_list)
{
	while (cmd_list)
	{
		if (!expand_cmd(shell_data, cmd_list->content))
			return (FAIL);
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}
