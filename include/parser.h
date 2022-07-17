/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:29:50 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/17 14:41:59 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

typedef t_list	t_pipeline_list;
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
	t_pipeline_list	*pipeline_list;
	t_operator_list	*operator_list;
}	t_parsed_data;

void	init_parsed_data(t_parsed_data *parsed_data);
void	destroy_parsed_data(t_parsed_data *parsed_data);

int		*parse(t_parsed_data *parsed_data, t_token_list *token_list);

#endif // !PARSER_H
