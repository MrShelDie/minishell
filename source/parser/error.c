/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 01:19:49 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/21 14:09:41 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include <stdio.h>

void	unexpected_token_error(t_token *token, size_t recursion_level)
{
	// TODO add program name
	printf(SYNTAX_ERR_MSG);
	if (token->id == TOKEN_PIPE)
		printf("'|'\n");
	else if (token->id == TOKEN_ANG_BR_L)
		printf("'<'\n");
	else if (token->id == TOKEN_ANG_BR_R)
		printf("'>'\n");
	else if (token->id == TOKEN_D_ANG_BR_L)
		printf("'<<'\n");
	else if (token->id == TOKEN_D_ANG_BR_R)
		printf("'>>'\n");
	else if (token->id == TOKEN_AND)
		printf("'&&'\n");
	else if (token->id == TOKEN_OR)
		printf("'||'\n");
	else if (token->id == TOKEN_PAR_L)
		printf("'('\n");
	else if (token->id == TOKEN_PAR_R
		|| (token->id == TOKEN_NEW_LINE && recursion_level > 0))
		printf("')'\n");
	else if (token->id == TOKEN_NEW_LINE && recursion_level == 0)
		printf("'newline'\n");
	else
		printf("'%s'\n", token->value);
}
