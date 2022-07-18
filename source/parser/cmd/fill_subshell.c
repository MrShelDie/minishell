/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:20:42 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/18 17:02:23 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser_private.h"
#include "libft.h"
#include <stdlib.h>

static t_token_list	*copy_sublist(t_token_list *begin, t_token_list *end)
{
	t_token_list	*list;
	t_token_list	*current;
	t_token_list	*new;

	if (begin == end)
	{
		unexpected_token_error(((t_token *)(begin->content))->id);
		return (NULL);
	}
	current = begin;
	while (current != end)
	{
		new = ft_lstnew(current->content);
		if (!new)
		{
			ft_lstclear(&list, free_token);
			return (NULL);
		}
		ft_lstadd_back(&list, new);
	}
	return (list);
}

static t_token_list	*get_token_sublist(t_token_list *token)
{
	size_t			open_par_count;
	t_token_list 	*begin;
	t_token_list 	*end;

	begin = token->next;
	open_par_count = 1;
	while (!(open_par_count == 1
		&& ((t_token *)(token->next->content))->id == TOKEN_PAR_R))
	{
		token = token->next;
		if (((t_token *)(token->content))->id == TOKEN_NEW_LINE)
		{
			unexpected_token_error(TOKEN_NEW_LINE);
			return (NULL);
		}
		else if (((t_token *)(token->content))->id == TOKEN_PAR_L)
			++open_par_count;
		else if (((t_token *)(token->next->content))->id == TOKEN_PAR_R)
			--open_par_count;
	}
	end = token;
	return (copy_sublist(begin, end));
}

static int	check_subshell(t_token_list *token)
{
	t_parsed_data	parsed_data;
	t_token_list	*token_sublist;
	int				result;

	init_parsed_data(&parsed_data);
	token_sublist = get_token_sublist(token);
	if (!token_sublist)
		return (FAIL);
	result = parse(&parsed_data, token);
	ft_lstclear(&token_sublist, free_token);
	destroy_parsed_data(&parsed_data);
	return (result);
}

int	fill_subshell(t_cmd *cmd, t_token_list **token)
{
	char			*arg;

	if (!check_subshell(*token))
		return (FAIL);
	(*token) = (*token)->next;
	arg = ft_strdup(((t_token *)((*token)->content))->value);
	if (!arg)
		return (FAIL);
	while (((t_token *)((*token)->content))->id != TOKEN_PAR_R)
	{
		if (!ft_strjoin(arg, " ")
			|| !ft_strjoin(arg, ((t_token *)((*token)->content))->value))
		{
			free(arg);
			return (FAIL);
		}
		(*token) = (*token)->next;
	}
	if (!vector_add(cmd->argv, arg))
		return (FAIL);
	(*token) = (*token)->next;
	free(arg);
	return (SUCCESS);
}
