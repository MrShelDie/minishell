/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:29:50 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/15 18:20:12 by gannemar         ###   ########.fr       */
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

t_parsed_data	*init_parsed_data(t_parsed_data *parsed_data);
void			destroy_parsed_data(t_parsed_data *parsed_data);

#endif // !PARSER_H
