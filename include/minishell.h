/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 23:01:33 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/10 01:05:14 by gannemar         ###   ########.fr       */
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
 * 
 * @note user_input accumulates data to be added to the history.
 * 		If we were adding data to the history line by line, then the
 * 		history, after the user enters the data in heredoc, would not
 * 		display the entire input in heredoc as a whole.
 */
typedef struct s_shell_data
{
	t_map		*env_map;
	t_vector	*env_vector;

	char		*user_input;
}	t_shell_data;

t_shell_data	*shell_init(char *const *envp);
void			shell_destroy(t_shell_data *shell_data);

int				shell_readline(t_shell_data *shell_data);
int				shell_read_heredoc(t_shell_data *shell_data);
void			shell_add_history(t_shell_data *shell_data);

#endif // !MINISHELL_H
