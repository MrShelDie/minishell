/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:29:39 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/15 17:38:43 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include <stdlib.h>

t_parsed_data	*init_parsed_data(t_parsed_data *parsed_data)
{
	if (parsed_data)
	{
		parsed_data->pipeline_list = NULL;
		parsed_data->operator_list = NULL;
	}
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

t_parsed_data	*parse(t_parsed_data *parsed_data, t_token_list *token_list)
{
	t_pipeline_list	*pipeline_list_node;
	t_operator_list	*operator_list_node;

	if (!parsed_data || !token_list)
		return (NULL);
	operator_list_node = NULL;
	while (operator_list_node
		&& *((t_operator *)(operator_list_node->content)) != OP_NEW_LINE)
	{
		pipeline_list_node = get_next_pipeline(&token_list);
		operator_list_node = get_next_operator(&token_list);
		ft_lstadd_back(&parsed_data->pipeline_list, pipeline_list_node);
		ft_lstadd_back(&parsed_data->operator_list, operator_list_node);
		if (!pipeline_list_node || !operator_list_node)
		{
			destroy_parsed_data(&parsed_data);
			return (NULL);
		}
	}
	return (parsed_data);
}
