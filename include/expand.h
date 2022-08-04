/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:04:22 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 15:31:16 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

int	expand_logic_group(const t_shell_data *shell_data, t_cmd_list *cmd_list);
int	expand_cmd(const t_shell_data *shell_data, t_cmd *cmd);

#endif
