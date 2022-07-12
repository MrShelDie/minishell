/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_private.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:08:14 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/12 16:38:16 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PRIVATE_H
# define LEXER_PRIVATE_H

# include "lexer.h"

int		is_special(char c);

t_list	*get_token(const char **pp_current_char, t_token_id id,
			size_t value_length);
size_t	get_word_token_length(const char *str);

#endif
