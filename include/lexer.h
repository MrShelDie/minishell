/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:26:38 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/13 16:14:29 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

typedef enum e_token_id
{
	END,
	PIPE,
	PAR_L,
	PAR_R,
	ANG_BR_L,
	ANG_BR_R,
	D_ANG_BR_L,
	D_ANG_BR_R,
	AND,
	OR,
	WORD
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

t_list	*get_token_list(const char *str);
void	free_token(void *token);

#endif
