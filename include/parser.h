/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:29:50 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 00:51:54 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "lexer.h"

typedef t_list	t_logic_group_list;
typedef t_list	t_operator_list;

typedef t_list	t_cmd_list;

typedef enum e_operator
{
	OP_OR,
	OP_AND,
	OP_NEW_LINE
}	t_operator;

typedef struct s_parsed_data
{
	t_logic_group_list	*logic_group_list;
	t_operator_list		*operator_list;
}	t_parsed_data;

void	destroy_parsed_data(t_parsed_data *parsed_data);

int 	parse_user_input(t_parsed_data *parsed_data, const char *str);

#endif // !PARSER_H
