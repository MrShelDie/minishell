/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 23:01:33 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/07 22:18:30 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

# include "map.h"
# include "vector.h"
# include "builtin.h"

# define SYNTAX_ERR_MSG "minishell: syntax error near unexpected token "

# define FAIL 0
# define SUCCESS 1
# define EXIT_PARSE_ERROR 2

/**
 * @brief General program data.
 */
typedef struct s_shell_data
{
	t_map		*env_map;
	t_vector	*env_vector;
	t_builtin	builtins[7];
	int			exit_status;
	bool		is_run;
}	t_shell_data;

typedef t_list				t_redir_list;
typedef t_list				t_arg_list;

typedef enum e_redir_id
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	REDIR_HEREDOC
}	t_redir_id;

typedef struct s_redir
{
	void		*value;
	t_redir_id	id;
}	t_redir;

typedef struct s_cmd
{
	t_vector		*argv;
	t_arg_list		*arg_list;
	t_redir_list	*redir_list;
	bool			is_subshell;
}	t_cmd;

void	init_shell_data(t_shell_data *shell_data, char *const *envp);
void	destroy_shell_data(t_shell_data *shell_data);

int		execute_user_input(t_shell_data *shell_data, char *user_input);

char	**split_env(const char *env_line);
size_t	vector_get_index_by_key(t_vector *vector, const char *key);

#endif // !MINISHELL_H
