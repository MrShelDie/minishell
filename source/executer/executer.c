/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/29 14:53:42 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand.h"
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

// -------------------------------------TEST-BEGIN------------------------------------

#include <stdio.h>

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
	printf("[%s %s] ", id, (char *)((t_redir *)redir)->value);
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
		if (!expand_pipe_group(shell_data, (t_cmd_list *)pipe_group->content))
		{
			ft_putstr_fd("ERROR\n", 2);
			// TODO handle error
			break ;
		}
		exit_status = execute_pipe_group(
				shell_data, (t_cmd_list *)pipe_group->content);
		pipe_group = pipe_group->next;
		if ((*(t_operator *)operator->content == OP_AND && exit_status != 0)
			|| (*(t_operator *)operator->content == OP_OR && exit_status == 0))
			pipe_group = pipe_group->next;
		if (*(t_operator *)operator->content == OP_NEW_LINE)
			break; ;
		operator = operator->next;
	}
	print_parsed_data(parsed_data);
}
