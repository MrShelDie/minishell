/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:27:03 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/19 14:13:42 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

/**
 * @brief Frees up the token's memory.
 * 
 * @param token Pointer to the token.
 */
void	destroy_token(void *token)
{
	if (!token)
		return ;
	if (((t_token *)token)->value)
		free(((t_token *)token)->value);
	free(token);
}
