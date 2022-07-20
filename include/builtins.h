/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:34:16 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 17:36:17 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "minishell.h"

int		ft_pwd(void);
int		ft_echo(char **argv, int iter);
int		ft_env(t_map_node *map);
int		ft_cd(char **av, t_shell_data *shell_data);
int		ft_unset(char **av, t_shell_data *data);
int		ft_export(t_cmd *cmd, t_shell_data *data);
void	ft_strcpy(char *dst, const char *src, size_t size);
char	**create_buff(char **map_buff, t_map *map, int *err);
char	**create_valbuf(char **value, t_map *map, int *err);
char	**sort_buff(char **buff, int len, char ***value);
void	delete_buff(char **m, char **v, int length);
int		ft_searchr(char *s, char c);
void	ft_strcpy(char *dst, const char *src, size_t size);
int		check_arg(char **av, int *check, int *option);
int		one_minus(char *cwd, t_shell_data *data, char *new_cwd);

#endif