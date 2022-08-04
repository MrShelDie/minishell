/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:20:42 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 13:14:31 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "../parser_private.h"
#include "shell_error.h"

static char	*get_subshell_arg(t_token_list **token_list_node)
{
	char	*subshell_arg;
	size_t	par_count;
	t_token	*curren_token;
	t_token	*next_token;

	subshell_arg = ft_strdup("");
	if (!subshell_arg)
	{
		print_error(strerror(errno));
		return (NULL);
	}
	par_count = 1;
	while (par_count > 0)
	{
		curren_token = (*token_list_node)->content;
		next_token = (*token_list_node)->next->content;
		if (curren_token->id == TOKEN_PAR_L)
			++par_count;
		else if (next_token->id == TOKEN_PAR_R)
			--par_count;
		if (!str_append_word(&subshell_arg, curren_token->value))
			return (NULL);
		(*token_list_node) = (*token_list_node)->next;
	}
	return (subshell_arg);
}

static t_token_list	*copy_sublist(
			t_token_list *begin, t_token_list *end, size_t recursion_level)
{
	t_token_list	*list;
	t_token_list	*current;

	if (begin == end)
	{
		unexpected_token_error(end->content, recursion_level);
		return (NULL);
	}
	list = NULL;
	current = begin;
	while (current != end)
	{
		if (!append_new_token(&list, ((t_token *)current->content)->id,
				((t_token *)current->content)->value))
			return (NULL);
		current = current->next;
	}
	return (append_new_token(&list, TOKEN_NEW_LINE, ""));
}

static t_token_list	*get_token_sublist(
	t_token_list *token, size_t recursion_level)
{
	size_t			open_par_count;
	t_token_list	*begin;
	t_token_list	*end;

	begin = token->next;
	open_par_count = 1;
	while (open_par_count > 0)
	{
		if (((t_token *)(token->content))->id == TOKEN_NEW_LINE)
		{
			unexpected_token_error(token->content, recursion_level);
			return (NULL);
		}
		else if (((t_token *)(token->next->content))->id == TOKEN_PAR_L)
			++open_par_count;
		else if (((t_token *)(token->next->content))->id == TOKEN_PAR_R)
			--open_par_count;
		token = token->next;
	}
	end = token;
	return (copy_sublist(begin, end, recursion_level));
}

static int	check_subshell(t_token_list *token, size_t *recursion_level)
{
	t_parsed_data	parsed_data;
	t_token_list	*token_sublist;
	int				result;

	ft_bzero(&parsed_data, sizeof(t_parsed_data));
	token_sublist = get_token_sublist(token, *recursion_level);
	if (!token_sublist)
		return (FAIL);
	++(*recursion_level);
	result = parse_tokens(&parsed_data, token_sublist);
	--(*recursion_level);
	ft_lstclear(&token_sublist, destroy_token);
	destroy_parsed_data(&parsed_data);
	return (result);
}

int	fill_subshell(
	t_cmd *cmd, t_token_list **token_list_node, size_t *recursion_level)
{
	char			*subshell_arg;
	t_arg_list		*new_arg_list_node;

	if (!check_subshell(*token_list_node, recursion_level))
		return (FAIL);
	(*token_list_node) = (*token_list_node)->next;
	subshell_arg = get_subshell_arg(token_list_node);
	if (!subshell_arg)
		return (FAIL);
	new_arg_list_node = ft_lstnew(subshell_arg);
	if (!new_arg_list_node)
	{
		print_error(strerror(errno));
		free(subshell_arg);
		return (FAIL);
	}	
	ft_lstadd_back(&cmd->arg_list, new_arg_list_node);
	cmd->is_subshell = true;
	(*token_list_node) = (*token_list_node)->next;
	return (SUCCESS);
}
