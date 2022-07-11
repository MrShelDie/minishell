/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 23:01:33 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/11 18:54:15 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "map.h"
# include "vector.h"

# define FAIL 0
# define SUCCESS 1

/**
 * @brief General program data
 */
typedef struct s_shell_data
{
	t_map		*env_map;
	t_vector	*env_vector;

	char		*user_input;
}	t_shell_data;

typedef struct s_cmd
{
	char				**data;
	char				*infile;
	char				*outfile;
}						t_cmd;

t_shell_data	*shell_init(char *const *envp);
void			shell_destroy(t_shell_data *shell_data);
int		executer(t_shell_data *shell_data, t_cmd *cmd);

#endif // !MINISHELL_H
