/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:04:22 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/05 15:49:34 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"
# include "parser.h"

int		expand_logic_group(
			const t_shell_data *shell_data, t_cmd_list *cmd_list);
int		expand_cmd(const t_shell_data *shell_data, t_cmd *cmd);

int		append_expanded_variable(
			const t_shell_data *shell_data, char **dst, char **src);
bool	is_variable(const char *str);

#endif
