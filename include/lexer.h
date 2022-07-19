/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:26:38 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/19 14:13:43 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

typedef t_list	t_token_list;

typedef enum e_token_id
{
	TOKEN_NEW_LINE,
	TOKEN_PIPE,
	TOKEN_PAR_L,
	TOKEN_PAR_R,
	TOKEN_ANG_BR_L,
	TOKEN_ANG_BR_R,
	TOKEN_D_ANG_BR_L,
	TOKEN_D_ANG_BR_R,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_WORD
}	t_token_id;

/**
 * @brief Token, contains an identifier and a pointer
 * 		to the first character of its value.
 */
typedef struct s_token
{
	t_token_id	id;
	char		*value;
}	t_token;

t_token_list	*get_token_list(const char *str);
void			destroy_token(void *token);

#endif
