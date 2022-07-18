/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 01:19:49 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/18 17:12:58 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include <stdio.h>

void	unexpected_token_error(t_token_id id)
{
	// TODO add program name
	printf("syntax error near unexpected token ");
	if (id == TOKEN_PIPE)
		printf("'|'\n");
	else if(id == TOKEN_PAR_L)
		printf("'('\n");
	else if(id == TOKEN_PAR_R)
		printf("')'\n");
	else if(id == TOKEN_ANG_BR_L)
		printf("'<'\n");
	else if(id == TOKEN_ANG_BR_R)
		printf("'>'\n");
	else if(id == TOKEN_D_ANG_BR_L)
		printf("'<<'\n");
	else if(id == TOKEN_D_ANG_BR_R)
		printf("'>>'\n");
	else if(id == TOKEN_AND)
		printf("'&&'\n");
	else if(id == TOKEN_OR)
		printf("'||'\n");
	else
		printf("'newline'\n");
}
