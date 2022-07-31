/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/31 22:24:47 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
#include "minishell.h"
#include "executer_private.h"
#include <stdlib.h>

/**
 * @brief Executes the parsed string entered by the user.
 * 
 * @param shell_data General shell data.
 * @param parsed_data  Parsed string entered by the user.
 */
int	executer(t_shell_data *shell_data, t_parsed_data *parsed_data)
{
	t_pipe_group_list	*pipe_group;
	t_operator_list		*operator;
	int					exit_status;

	pipe_group = parsed_data->pipe_group_list;
	operator = parsed_data->operator_list;
	if (!read_all_heredocs(pipe_group))
	{
		// TODO handle error
		return (EXIT_FAILURE);
	}
	while (pipe_group)
	{
		if (!expand_pipe_group(shell_data, (t_cmd_list *)pipe_group->content))
		{
			// TODO handle error
			return (EXIT_FAILURE);
		}
		if (((t_cmd_list *)pipe_group->content)->next)
			exit_status = exec_pipe_group(
				shell_data, (t_cmd_list *)pipe_group->content);
		else
			exit_status = exec_simple_cmd(
				shell_data, (t_cmd_list *)pipe_group->content);
		pipe_group = pipe_group->next;
		if ((*(t_operator *)operator->content == OP_AND && exit_status != 0)
			|| (*(t_operator *)operator->content == OP_OR && exit_status == 0))
			pipe_group = pipe_group->next;
		if (*(t_operator *)operator->content == OP_NEW_LINE)
			break ;
		operator = operator->next;
	}
	return (exit_status);
}
