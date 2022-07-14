/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:29:39 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/15 00:18:05 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

static t_parsed_data	*init_parsed_data(void)
{
	t_parsed_data	*parsed_data;

	parsed_data = (t_parsed_data *)malloc(sizeof(t_parsed_data));
	if (parsed_data)
	{
		parsed_data->pipe_list = NULL;
		parsed_data->operator_list = NULL;
	}
	return (parsed_data);
}

static void	destroy_parsed_data(t_parsed_data **parsed_data)
{
	if (!parsed_data || !*parsed_data)
		return ;
	if ((*parsed_data)->pipe_list)
		// TODO destroy
	if ((*parsed_data)->operator_list)
		// TODO destroy
	*parsed_data = NULL;
}

static t_pipe_list	*get_next_pipe(t_list **token)
{
	t_pipe_list	*new_pipe;
	t_cmd_list	*cmd_list;
	t_cmd		*cmd;

	// TODO
}

static t_operator_list	*get_next_operator(t_list **token)
{
	// TODO
}

t_parsed_data	*parse(t_list *token_list)
{
	t_parsed_data	*parsed_data;
	t_pipe_list		*new_pipe;
	t_operator_list	*new_operator;

	if (!token_list)
		return (NULL);
	parsed_data = init_parsed_data();
	if (!parsed_data)
		return (NULL);
	while (((t_token *)(token_list->content))->id != NEW_LINE)
	{
		new_pipe = get_next_pipe(&token_list);
		new_operator = get_next_operator(&token_list);
		ft_lstadd_back(&parsed_data->pipe_list, new_pipe);
		ft_lstadd_back(&parsed_data->operator_list, new_operator);
		if (!new_pipe || !new_operator)
		{
			destroy_parsed_data(&parsed_data);
			return (NULL);
		}
	}
	return (parsed_data);
}
