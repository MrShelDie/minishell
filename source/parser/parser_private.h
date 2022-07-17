/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:34:56 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/17 13:37:20 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_PRIVATE_H
# define PARSER_PRIVATE_H

# include "parser.h"
# include "lexer.h"
# include "minishell.h"

t_pipeline_list	*get_next_pipeline(t_token_list **token);
t_operator_list	*get_next_operator(t_token_list **token);

int				fill_redir(t_cmd *cmd, t_token_list **token, t_redir_id redir_id);
int				fill_argv(t_cmd *cmd, t_token_list **token);
int				fill_subshell(t_cmd *cmd, t_token_list **token);

#endif // !PARSER_PRIVATE_H
