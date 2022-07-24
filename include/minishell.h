/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 23:01:33 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/24 13:10:53 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "map.h"
# include "vector.h"
# include "libft.h"
# include <stdbool.h>

# define FAIL 0
# define SUCCESS 1

/**
 * @brief General program data.
 */
typedef struct s_shell_data
{
	t_map		*env_map;
	t_vector	*env_vector;

	char		*program_name;
}	t_shell_data;

typedef t_list	t_redir_list;
typedef t_list	t_arg_list;

typedef enum e_redir_id
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	REDIR_HEREDOC
}	t_redir_id;

typedef struct s_redir
{
	char		*value;
	t_redir_id	id;
}	t_redir;

typedef struct s_cmd
{
	t_vector		*argv;
	t_arg_list		*arg_list;
	t_redir_list	*redir_list;
	bool			is_subshell;
}	t_cmd;

t_shell_data	*shell_init(t_shell_data *shell_data, char *const *argv,
					char *const *envp);
void			shell_destroy(t_shell_data *shell_data);

#endif // !MINISHELL_H
