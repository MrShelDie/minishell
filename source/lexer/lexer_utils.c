/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:27:03 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/11 17:32:08 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_private.h"

/**
 * @brief Frees up the token's memory.
 * 
 * @param token Pointer to the token.
 */
void	free_token(void *token)
{
	free(((t_token *)token)->value);
	free(token);
}

int	is_special(char c)
{
	if (c == '\0' || c == '|' || c == '=' || c == '(' || c == ')'
		|| c == '<' || c == '>')
			return (1);
	return (0);
}
