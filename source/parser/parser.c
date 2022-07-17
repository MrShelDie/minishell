/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:29:39 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/17 14:41:44 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include "libft.h"
#include <stdlib.h>

void	init_parsed_data(t_parsed_data *parsed_data)
{
	if (parsed_data)
		ft_bzero(parsed_data, sizeof(t_parsed_data));
	return (parsed_data);
}

void	destroy_parsed_data(t_parsed_data *parsed_data)
{
	if (!parsed_data)
		return ;
	if (parsed_data->pipeline_list)
		// TODO destroy
	if (parsed_data->operator_list)
		// TODO destroy
}

int	*parse(t_parsed_data *parsed_data, t_token_list *token_list)
{
	t_pipeline_list	*pipeline_list_node;
	t_operator_list	*operator_list_node;

	if (!parsed_data || !token_list)
		return (FAIL);
	operator_list_node = NULL;
	while (operator_list_node
		&& *((t_operator *)(operator_list_node->content)) != OP_NEW_LINE)
	{
		pipeline_list_node = get_next_pipeline(&token_list);
		operator_list_node = get_next_operator(&token_list);
		ft_lstadd_back(&parsed_data->pipeline_list, pipeline_list_node);
		ft_lstadd_back(&parsed_data->operator_list, operator_list_node);
		if (!pipeline_list_node || !operator_list_node)
			return (FAIL);
	}
	return (SUCCESS);
}
