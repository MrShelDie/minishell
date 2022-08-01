/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:44:54 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/01 14:49:16 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_shell_data	t_shell_data;
typedef int					(*t_builtin)(t_shell_data *data, char **av);

typedef enum e_builtin_nb
{
	CD,
	ECHO,
	ENV,
	EXPORT,
	PWD,
	UNSET,
	NONE
}	t_builtin_nb;

int				ft_pwd(t_shell_data *data, char **av);
int				ft_echo(t_shell_data *data, char **av);
int				ft_env(t_shell_data *data, char **av);
int				ft_cd(t_shell_data *data, char **av);
int				ft_unset(t_shell_data *data, char **av);
int				ft_export(t_shell_data *data, char **av);

t_builtin_nb	get_builtin_nb(const char *cmd);

#endif
