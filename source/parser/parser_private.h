/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:34:56 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 13:12:46 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_PRIVATE_H
# define PARSER_PRIVATE_H

# include "parser.h"
# include "lexer.h"
# include "minishell.h"

int					parse_tokens(
						t_parsed_data *parsed_data, t_token_list *token_list);

t_logic_group_list	*get_next_logic_group_list_node(
						t_token_list **token, size_t *recursion_level);
t_operator_list		*get_next_operator_list_node(
						t_token_list **token, size_t recursion_level);

t_cmd				*get_next_cmd(
						t_token_list **token, size_t *recursion_level);

int					fill_redir(t_cmd *cmd, t_token_list **token,
						t_redir_id redir_id, size_t *recursion_level);
int					fill_argv(
						t_cmd *cmd, t_token_list **token);
int					fill_subshell(t_cmd *cmd,
						t_token_list **token, size_t *recursion_level);

char				*str_append_word(char **dst, const char *src);

void				destroy_cmd(void *cmd);
void				destroy_redir(void *redir);
void				destroy_logic_group(void *pipeline);

void				unexpected_token_error(
						t_token *token, size_t recursion_level);

t_token_list		*append_new_token(
						t_token_list **list, t_token_id token_id, char *value);

#endif // !PARSER_PRIVATE_H
