/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:20:42 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/19 18:09:08 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser_private.h"
#include "libft.h"
#include <stdlib.h>

static t_token_list	*add_token(t_token_list **list, t_token_id token_id)
{
	t_token_list	*new_node;
	t_token			*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		ft_lstclear(list, destroy_token);
		return (NULL);
	}
	new_token->id = token_id;
	new_token->value = NULL;
	new_node = ft_lstnew(new_token);
	if (!new_node)
	{
		destroy_token(new_token);
		ft_lstclear(list, destroy_token);
		return (NULL);
	}
	ft_lstadd_back(list, new_node);
	return (*list);
}

static t_token_list	*copy_sublist(t_token_list *begin, t_token_list *end)
{
	t_token_list	*list;
	t_token_list	*current;

	if (begin == end)
	{
		unexpected_token_error(((t_token *)(end->content))->id);
		return (NULL);
	}
	list = NULL;
	current = begin;
	while (current != end)
	{
		if (!add_token(&list, ((t_token *)current->content)->id))
			return (NULL);
		current = current->next;
	}
	return (add_token(&list, TOKEN_NEW_LINE));
}

static t_token_list	*get_token_sublist(t_token_list *token)
{
	size_t			open_par_count;
	t_token_list 	*begin;
	t_token_list 	*end;

	begin = token->next;
	open_par_count = 1;
	while (open_par_count > 0)
	{
		if (((t_token *)(token->content))->id == TOKEN_NEW_LINE)
		{
			unexpected_token_error(TOKEN_NEW_LINE);
			return (NULL);
		}
		else if (((t_token *)(token->next->content))->id == TOKEN_PAR_L)
			++open_par_count;
		else if (((t_token *)(token->next->content))->id == TOKEN_PAR_R)
			--open_par_count;
		token = token->next;
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
	result = parse(&parsed_data, token_sublist);
	ft_lstclear(&token_sublist, destroy_token);
	destroy_parsed_data(&parsed_data);
	return (result);
}

char	*str_append_word(char **dst, const char *src)
{
	char	*new_str;

	new_str = ft_strjoin(*dst, " ");
	if (!new_str)
		return (NULL);
	free(*dst);
	*dst = new_str;
	new_str = ft_strjoin(new_str, src);
	if (!new_str)
		return (NULL);
	free(*dst);
	*dst = new_str;
	return (*dst);
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
	(*token) = (*token)->next;
	while (((t_token *)((*token)->content))->id != TOKEN_PAR_R)
	{
		if (!str_append_word(&arg, ((t_token *)((*token)->content))->value))
		{
			free(arg);
			return (FAIL);
		}
		(*token) = (*token)->next;
	}
	if (!vector_add(cmd->argv, arg))
		return (FAIL);
	cmd->is_subshell = true;
	(*token) = (*token)->next;
	free(arg);
	return (SUCCESS);
}
