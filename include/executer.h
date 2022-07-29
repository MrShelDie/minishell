/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:38:17 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/29 19:00:57 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"
# include "parser.h"

# define CMD_PATH 2

typedef struct s_pipe
{
    pid_t   *pid;
    int     **tube;
    int     out;
    size_t  len;
    int     in;
    int     here_doc;
    char    *path;
    char    *cmd;
    char    **cmd_path;
}               t_pipe;

void	executer(t_shell_data *shell_data, t_parsed_data *parsed_data);
int	    create_heredoc(char **stop_word);
int     pipex_part(t_shell_data *data, t_cmd_list *cmd_list);
int	    replace_names_in_heredoc(t_map *env, char **file_name);
int	    builtins(t_shell_data *shell_data, t_vector *cmd, t_pipe *pipex);
int	    infile(t_pipe *pipex, t_redir *redir);
int	    outfile(t_pipe *pipex, t_redir *redir);
int	    create_pipes(t_pipe *pipex);
int     start_pipex(t_pipe *pipex, t_shell_data *data, t_cmd_list *cmd_list);
void    ft_strdel(char **as);
void    ft_strdel_all(char **as);
void    ft_strdel_all2(int **as);
char	*get_cmd(char **paths, char *cmd);
void	close_tube(t_pipe *pipex);
int     dup_tube_and_redir( t_pipe *pipex, t_shell_data *data, \
            t_cmd_list *cmd_list, int i);
int     dup_redir(t_pipe *pipex, t_redir_list *redir_list, t_shell_data *data);
int     dup_pipe(t_pipe *pipex, size_t i);
void    delete_all_pipex_struct(t_pipe *pipex);
int    child(
        t_pipe *pipex, t_shell_data *data, t_cmd_list *cmd_list, int i);
void	delete_buff_here(char **av);
int	    append_regular_str(char **dst, char **src);
int	    replace_with_expanded_str(const t_map *env_map, char **str);

#endif
