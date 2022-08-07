/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:13:34 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/07 18:16:23 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "../parser_private.h"
#include "shell_error.h"
#include "libft.h"

int	fill_arg_list(t_cmd *cmd, t_token_list **token_list_node)
{
	char		*value_copy;
	t_arg_list	*new_node;

	value_copy = ft_strdup(((t_token *)(*token_list_node)->content)->value);
	if (!value_copy)
	{
		print_error(strerror(errno));
		return (FAIL);
	}
	new_node = ft_lstnew(value_copy);
	if (!value_copy)
	{
		print_error(strerror(errno));
		free(value_copy);
		return (FAIL);
	}	
	ft_lstadd_back(&cmd->arg_list, new_node);
	(*token_list_node) = (*token_list_node)->next;
	return (SUCCESS);
}
