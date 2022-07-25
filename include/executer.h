/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:38:17 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/20 18:41:03 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"
# include "parser.h"

typedef struct s_pipe
{
    pid_t   *pid;
    int     **tube;
    int     out;
    size_t  len;
    int     in;
    char    *path;
    char    *cmd;
    char    **cmd_path;
}               t_pipe;

void	executer(t_shell_data *shell_data, t_parsed_data *parsed_data);
int	    create_heredoc(t_map *env, const char *stop_word);
int     pipex_part(t_shell_data *data, t_cmd_list *cmd_list);

#endif
