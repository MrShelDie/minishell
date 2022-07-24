/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:13:34 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/24 13:34:43 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser_private.h"
#include "libft.h"
#include <stdlib.h>

int	fill_argv(t_cmd *cmd, t_token_list **pp_token_list_node)
{
	char		*value_copy;
	t_arg_list	*new_node;

	value_copy = ft_strdup(((t_token *)(*pp_token_list_node)->content)->value);
	if (!value_copy)
		return (FAIL);
	new_node = ft_lstnew(value_copy);
	if (!value_copy)
	{
		free(value_copy);
		return (FAIL);
	}	
	ft_lstadd_back(&cmd->arg_list, new_node);
	(*pp_token_list_node) = (*pp_token_list_node)->next;
	return (SUCCESS);
}
