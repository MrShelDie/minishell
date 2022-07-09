/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 23:01:33 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/09 20:41:12 by gannemar         ###   ########.fr       */
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

t_shell_data	*shell_init(char *const *envp);
void			shell_destroy(t_shell_data *shell_data);

#endif // !MINISHELL_H
