/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:34:56 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/20 15:11:42 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_PRIVATE_H
# define PARSER_PRIVATE_H

# include "parser.h"
# include "lexer.h"
# include "minishell.h"

t_pipe_group_list	*get_next_pipe_group(
						t_token_list **token, size_t *recursion_level);
t_operator_list		*get_next_operator(
						t_token_list **token, size_t recursion_level);

t_cmd				*get_next_cmd(t_token_list **token, size_t *recursion_level);

int					fill_redir(t_cmd *cmd, t_token_list **token,
						t_redir_id redir_id, size_t *recursion_level);
int					fill_argv(
						t_cmd *cmd, t_token_list **token);
int					fill_subshell(
						t_cmd *cmd, t_token_list **token, size_t *recursion_level);

void				destroy_cmd(void *cmd);
void				destroy_redir(void *redir);
void				destroy_pipe_group(void *pipeline);

void				write_unexpected_token_error(
						t_token *token, size_t recursion_level);

#endif // !PARSER_PRIVATE_H
