/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/21 12:55:18 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "builtins.h"
#include "minishell.h"

static int	builtins(t_shell_data *shell_data, t_vector *cmd)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd->data[i], "echo", 4) == 0)
	{
		i++;
		if (ft_echo(cmd->data, i) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "pwd", 3) == 0)
	{
		i++;
		if (ft_pwd() == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "env", 3) == 0)
	{
		i++;
		if (ft_env(shell_data->env_map->head) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "cd", 2) == 0)
	{
		i++;
		if (ft_cd(cmd->data, shell_data) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "unset", 5) == 0)
	{
		i++;
		if (ft_unset(cmd->data, shell_data) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "export", 6) == FAIL)
	{
		if (ft_export(cmd, shell_data) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

static int	execute_pipe_group(t_shell_data *shell_data, t_cmd_list *cmd_list)
{
	if (!builtins(shell_data, ((t_cmd *)(cmd_list->content))->argv))
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief Executes the parsed string entered by the user.
 * 
 * @param shell_data General shell data.
 * @param parsed_data  Parsed string entered by the user.
 */
void	executer(t_shell_data *shell_data, t_parsed_data *parsed_data)
{
	t_pipe_group_list	*pipe_group;
	t_operator_list		*operator;
	int					exit_status;

	pipe_group = parsed_data->pipe_group_list;
	operator = parsed_data->operator_list;
	while (true)
	{
		// TODO PIPE GROUP PREPARE
		exit_status = execute_pipe_group(
				shell_data, (t_cmd_list *)pipe_group->content);
		pipe_group = pipe_group->next;
		if ((*(t_operator *)operator->content == OP_AND && exit_status != 0)
			|| (*(t_operator *)operator->content == OP_OR && exit_status == 0))
			pipe_group = pipe_group->next;
		if (*(t_operator *)operator->content == OP_NEW_LINE)
			return ;
		operator = operator->next;
	}
}
