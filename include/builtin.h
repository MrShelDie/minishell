/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:44:54 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/05 15:48:24 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_shell_data	t_shell_data;
typedef struct s_vector		t_vector;
typedef int					(*t_builtin)(t_shell_data *data, t_vector *vector);

typedef enum e_builtin_nb
{
	BUILTIN_CD,
	BUILTIN_ECHO,
	BUILTIN_ENV,
	BUILTIN_EXPORT,
	BUILTIN_EXIT,
	BUILTIN_PWD,
	BUILTIN_UNSET,
	BUILTIN_NONE
}	t_builtin_nb;

int				ft_pwd(t_shell_data *data, t_vector *vector);
int				ft_echo(t_shell_data *data, t_vector *vector);
int				ft_env(t_shell_data *data, t_vector *vector);
int				ft_cd(t_shell_data *data, t_vector *vector);
int				ft_unset(t_shell_data *data, t_vector *vector);
int				ft_export(t_shell_data *data, t_vector *vector);
int				ft_exit(t_shell_data *data, t_vector *vector);

t_builtin_nb	get_builtin_nb(const char *cmd);

#endif
