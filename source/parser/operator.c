/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:34:29 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 12:23:47 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "parser_private.h"
#include "shell_error.h"

static t_operator_list	*create_operator_list_node(t_operator id)
{
	t_operator_list	*operator_list_node;
	t_operator		*operator;

	operator = malloc(sizeof(t_operator));
	if (!operator)
	{
		print_error(strerror(errno));
		return (NULL);
	}
	*operator = id;
	operator_list_node = ft_lstnew(operator);
	if (!operator_list_node)
	{
		print_error(strerror(errno));
		free(operator);
	}
	return (operator_list_node);
}

t_operator_list	*get_next_operator_list_node(
	t_token_list **token_list_node, size_t recursion_level)
{
	t_token_id		token_id;

	if (!token_list_node || !*token_list_node)
		return (NULL);
	token_id = ((t_token *)((*token_list_node)->content))->id;
	if (token_id == TOKEN_OR)
	{
		*token_list_node = (*token_list_node)->next;
		return (create_operator_list_node(OP_OR));
	}
	else if (token_id == TOKEN_AND)
	{
		*token_list_node = (*token_list_node)->next;
		return (create_operator_list_node(OP_AND));
	}
	else if (token_id == TOKEN_NEW_LINE)
	{
		*token_list_node = (*token_list_node)->next;
		return (create_operator_list_node(OP_NEW_LINE));
	}
	unexpected_token_error((*token_list_node)->content, recursion_level);
	return (NULL);
}
