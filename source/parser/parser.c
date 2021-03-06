/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:29:39 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/20 15:04:13 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include "libft.h"
#include <stdlib.h>

void	init_parsed_data(t_parsed_data *parsed_data)
{
	if (parsed_data)
		ft_bzero(parsed_data, sizeof(t_parsed_data));
}

void	destroy_parsed_data(t_parsed_data *parsed_data)
{
	if (!parsed_data)
		return ;
	if (parsed_data->pipe_group_list)
		ft_lstclear(&parsed_data->pipe_group_list, destroy_pipe_group);
	if (parsed_data->operator_list)
		ft_lstclear(&parsed_data->operator_list, free);
}

int	parse(t_parsed_data *parsed_data, t_token_list *token_list)
{
	t_pipe_group_list	*pipe_group;
	t_operator_list		*operator;
	static size_t		recursion_level = 0;

	if (!parsed_data || !token_list)
		return (FAIL);
	operator = NULL;
	while (!(operator
			&& *((t_operator *)(operator->content)) == OP_NEW_LINE))
	{
		pipe_group = get_next_pipe_group(&token_list, &recursion_level);
		if (!pipe_group)
			return (FAIL);
		operator = get_next_operator(&token_list, recursion_level);
		if (!operator)
			return (FAIL);
		ft_lstadd_back(&parsed_data->pipe_group_list, pipe_group);
		ft_lstadd_back(&parsed_data->operator_list, operator);
	}
	return (SUCCESS);
}
