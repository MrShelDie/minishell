/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:29:50 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/15 00:04:24 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

typedef t_list	t_pipe_list;
typedef t_list	t_operator_list;

typedef t_list	t_cmd_list;

typedef struct s_parsed_data
{
	t_pipe_list		*pipe_list;
	t_operator_list	*operator_list;
}	t_parsed_data;

#endif // !PARSER_H
