/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/08/06 18:14:28 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "parser.h"
#include "expand.h"
#include "executer_private.h"
#include "shell_signal.h"

int	execute_parsed_line(t_shell_data *shell_data, t_parsed_data *parsed_data)
{
	t_logic_group_list	*logic_group_list;
	t_cmd_list			*cmd_list;
	t_operator_list		*operator_list;

	logic_group_list = parsed_data->logic_group_list;
	cmd_list = logic_group_list->content;
	operator_list = parsed_data->operator_list;
	if (!read_all_heredocs(logic_group_list))
		return (EXIT_FAILURE);
	set_fork_signals();
	if (logic_group_list->next || cmd_list->next)
		return (execute_logic_group_list(shell_data,
				logic_group_list, operator_list));
	return (execute_simple_cmd(shell_data, logic_group_list));
}
