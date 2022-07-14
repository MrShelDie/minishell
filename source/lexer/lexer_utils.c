/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:27:03 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/14 19:10:16 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

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
