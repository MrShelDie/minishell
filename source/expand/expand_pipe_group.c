/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pipe_group.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:54:19 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/29 14:32:42 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expand_private.h"
#include <stdlib.h>

static int	expand_arg_list(const t_map *env_map, t_arg_list **arg_list)
{
	t_arg_list	**current;
	t_arg_list	*next;
	t_asterisk	asterisk;

	current = arg_list;
	while (*current)
	{
		next = (*current)->next;
		if (!fill_asterisk_map(&asterisk, (*current)->content))
			return (FAIL);
		if (check_expansion((*current)->content)
			&& !replace_with_expanded_str(env_map, &(*current)->content))
			return (FAIL);
		if (asterisk.contains_wildcard
			&& !insert_matched_wildcard_arg_list(current, next, asterisk.array))
			return (FAIL);
		free_asterisk_map(&asterisk);
		current = &(*current)->next;
	}
	return (SUCCESS);
}

static int	expand_redir_list(
	const t_shell_data *shell_data, t_redir_list *redir_list)
{
	t_asterisk	asterisk;

	while (redir_list)
	{
		if (!fill_asterisk_map(
			&asterisk, ((t_redir *)redir_list->content)->value))
			return (FAIL);
		if (check_expansion(((t_redir *)redir_list->content)->value)
			&& !replace_with_expanded_str(shell_data->env_map,
				&((t_redir *)redir_list->content)->value))
			return (FAIL);
		if (asterisk.contains_wildcard && !replace_matched_redir(
				shell_data, &((t_redir *)redir_list->content)->value,
				asterisk.array))
			return (FAIL);
		free_asterisk_map(&asterisk);
		redir_list = redir_list->next;
	}
	return (SUCCESS);
}

static int	expand_cmd(const t_shell_data *shell_data, t_cmd *cmd)
{
	if (!expand_arg_list(shell_data->env_map, &cmd->arg_list)
		|| !expand_redir_list(shell_data, cmd->redir_list)
	)
		return (FAIL);
	ft_strtolower(cmd->arg_list->content);
	cmd->argv = vector_create_from_list(cmd->arg_list);
	if (!cmd->argv)
		return (FAIL);
	return (SUCCESS);
}

int	expand_pipe_group(const t_shell_data *shell_data, t_cmd_list *cmd_list)
{
	while (cmd_list)
	{
		if (!expand_cmd(shell_data, cmd_list->content))
			return (FAIL);
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}
