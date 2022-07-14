/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 23:01:33 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/15 00:00:35 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "map.h"
# include "vector.h"

# define FAIL 0
# define SUCCESS 1

/**
 * @brief General program data.
 */
typedef struct s_shell_data
{
	t_map		*env_map;
	t_vector	*env_vector;
}	t_shell_data;

typedef t_list	t_redir_list;

typedef enum e_redir_id
{
	IN,
	OUT,
	OUT_APPEND,
	HEREDOC
}	t_redir_id;

typedef struct s_redir
{
	char		*value;
	t_redir_id	id;
}	t_redir;

typedef struct s_cmd
{
	t_vector		*argv;
	t_redir_list	*redir_list;
}	t_cmd;

t_shell_data	*shell_init(char *const *envp);
void			shell_destroy(t_shell_data *shell_data);

#endif // !MINISHELL_H
