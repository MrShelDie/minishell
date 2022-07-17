/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 12:48:20 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/17 13:12:19 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include "libft.h"
#include <stdlib.h>

static t_redir	*create_redir(t_redir_id id, char *value)
{
	t_redir	*redir;
	char	*redir_value_copy;

	redir_value_copy = ft_strdup(value);
	if (!redir_value_copy)
		return (NULL);
	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
	{
		free(redir_value_copy);
		return (NULL);
	}
	redir->id = id;
	redir->value = redir_value_copy;
	return (redir);
}

int	fill_redir(t_cmd *cmd, t_token_list **token, t_redir_id redir_id)
{
	t_redir	*redir;

	(*token) = (*token)->next;
	if (((t_token *)((*token)->content))->id != TOKEN_WORD)
		// TODO UNEXPECTED TOKEN ERROR
	redir = create_redir(redir_id, ((t_token *)((*token)->content))->value);
	if (!redir)
		return (FAIL);
	ft_lstadd_back(&cmd->redir_list, redir);
	(*token) = (*token)->next;
	return (SUCCESS);
}
