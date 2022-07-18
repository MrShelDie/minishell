/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:13:34 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/18 19:54:09 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser_private.h"
#include "libft.h"

int	fill_argv(t_cmd *cmd, t_token_list **token)
{
	if (!vector_add(cmd->argv, ((t_token *)((*token)->content))->value))
		return (FAIL);
	(*token) = (*token)->next;
	return (SUCCESS);
}
