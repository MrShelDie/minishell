/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/08/02 20:00:44 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expand.h"
#include "executer_private.h"
#include <stdlib.h>

int	execute_parsed_line(t_shell_data *shell_data, t_parsed_data *parsed_data)
{
	t_pipe_group_list	*pipe_group;
	t_operator_list		*operator_list;

	pipe_group = parsed_data->pipe_group_list;
	operator_list = parsed_data->operator_list;
	if (!read_all_heredocs(pipe_group))
		return (EXIT_FAILURE);
	if (pipe_group->next)
		return (execute_pipe_group_list(shell_data, pipe_group, operator_list));
	return (execute_simple_cmd(shell_data, pipe_group));
}
