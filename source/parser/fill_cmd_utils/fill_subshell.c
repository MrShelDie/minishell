/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:20:42 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/17 16:49:27 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include "libft.h"



static int	check_subshell(t_token_list *token)
{
	t_parsed_data	parsed_data;
	int				result;

	init_parsed_data(&parsed_data);
	// TODO cut list
	result = parse(&parsed_data, token);
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
