/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:26:50 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 16:07:25 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_PRIVATE_H
# define EXECUTER_PRIVATE_H

# include "executer.h"
# include "shell_error.h"
# include <unistd.h>

# define CMD_PATH 2

typedef struct s_pipe
{
	pid_t	*pids;
	int		**tube;
	size_t	pipe_count;
	char	*path;
	char	*cmd;
	char	**cmd_path;
}	t_pipe;

int		execute_logic_group_list(t_shell_data *shell_data,
			t_logic_group_list *pipe_group, t_operator_list *operator_list);
int		execute_simple_cmd(
			t_shell_data *shell_data, t_logic_group_list *pipe_group);

int		read_all_heredocs(t_logic_group_list *pipe_group);

char	*generate_file_name(char *pattenr, char *stop_word);

int		dup_redir(t_redir_list *redir_list, t_shell_data *data);

int		dup_heredoc(t_map *env, t_redir *redir);
int		dup_infile(const char *file_name);
int		dup_outfile(const char *file_name);
int		dup_outfile_append(const char *file_name);

char	**get_cmd_paths(t_map *env);
char	*get_cmd(char **paths, char *cmd);

int		wait_all_pids(pid_t *pids, size_t size);
int		exec_init_pipex(t_pipe *pipex,
			t_shell_data *data, t_cmd_list *cmd_list);
void	exec_utils(t_pipe *pipex,
			t_shell_data *shell_data, t_cmd *cmd, int *exit_builtin);

void	delete_saved_stdio(int dupped_io_fd[2]);
int		save_stdio(int dupped_io_fd[2]);
int		restore_stdio(int dupped_io_fd[2]);

// ---------------------------------------

int		expand_var_in_heredoc(t_map *env, void **file_name);
int		create_pipes(t_pipe *pipex);
int		init_pipex(t_pipe *pipex, t_shell_data *data, t_cmd_list *cmd_list);
void	ft_strdel(char **as);
void	ft_strdel_cmd_path(char **as);
void	ft_strdel_tube(int **as);
void	close_tube(t_pipe *pipex);
int		dup_pipe(t_pipe *pipex, size_t i);
void	destroy_pipex(t_pipe *pipex);

int		replace_expanded_var(const t_map *env_map, char **str);

#endif
