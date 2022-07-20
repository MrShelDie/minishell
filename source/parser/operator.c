/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:34:29 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/20 15:11:48 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include <stdlib.h>

static t_operator_list	*create_operator_list_node(t_operator id)
{
	t_operator_list	*operator_list_node;
	t_operator		*operator;

	operator = (t_operator *)malloc(sizeof(t_operator));
	if (!operator)
		return (NULL);
	*operator = id;
	operator_list_node = ft_lstnew(operator);
	if (!operator_list_node)
		free(operator);
	return (operator_list_node);
}

t_operator_list	*get_next_operator(t_token_list **token, size_t recursion_level)
{
	t_token_id		token_id;

	if (!token || !*token)
		return (NULL);
	token_id = ((t_token *)((*token)->content))->id;
	if (token_id == TOKEN_OR)
	{
		*token = (*token)->next;
		return (create_operator_list_node(OP_OR));
	}
	else if (token_id == TOKEN_AND)
	{
		*token = (*token)->next;
		return (create_operator_list_node(OP_AND));
	}
	else if (token_id == TOKEN_NEW_LINE)
	{
		*token = (*token)->next;
		return (create_operator_list_node(OP_NEW_LINE));
	}
	write_unexpected_token_error((*token)->content, recursion_level);
	return (NULL);
}
