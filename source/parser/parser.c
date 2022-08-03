/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:29:39 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 01:18:59 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include "libft.h"
#include <stdlib.h>

void	destroy_parsed_data(t_parsed_data *parsed_data)
{
	if (!parsed_data)
		return ;
	ft_lstclear(&parsed_data->logic_group_list, destroy_logic_group);
	ft_lstclear(&parsed_data->operator_list, free);
}

/*
**  The function fills in the list of logical groups and the list
**	of operators standing between logical groups in the user input line.
**	
**	If the parser encountered parentheses, then the tokens of the substring
**  in parentheses are passed recursively to this function, having previously
**  increased the recursion level variable.
**
**  The recursion level variable is used to correctly display error messages.
*/
int	parse_tokens(t_parsed_data *parsed_data, t_token_list *token_list)
{
	t_logic_group_list	*logic_group_list_node;
	t_operator_list		*operator_list_node;
	t_operator			*operator;
	static size_t		recursion_level = 0;

	operator_list_node = NULL;
	operator = NULL;
	while (!operator || *operator != OP_NEW_LINE)
	{
		logic_group_list_node = get_next_logic_group_list_node(
			&token_list, &recursion_level);
		if (!logic_group_list_node)
			return (FAIL);
		ft_lstadd_back(&parsed_data->logic_group_list, logic_group_list_node);
		operator_list_node = get_next_operator_list_node(
			&token_list, recursion_level);
		if (!operator_list_node)
			return (FAIL);
		ft_lstadd_back(&parsed_data->operator_list, operator_list_node);
		operator = operator_list_node->content;
	}
	return (SUCCESS);
}

int parse_user_input(t_parsed_data *parsed_data, const char *str)
{
	t_token_list	*token_list;
	int				parse_status;

	if (!check_closed_quotes(str))
		return (FAIL);
	token_list = get_token_list(str);
	if (!token_list)
		return (FAIL);
	parse_status = parse_tokens(parsed_data, token_list);
	ft_lstclear(&token_list, destroy_token);
	return (parse_status);
}
