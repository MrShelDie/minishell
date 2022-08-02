/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:04:22 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/02 19:57:49 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

#include "minishell.h"

int	expand_pipe_group(const t_shell_data *shell_data, t_cmd_list *cmd_list);
int	expand_cmd(const t_shell_data *shell_data, t_cmd *cmd);

#endif
