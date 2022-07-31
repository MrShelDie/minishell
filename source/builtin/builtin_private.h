/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_private.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:04:46 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/31 21:50:58 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_PRIVATE_H
# define BUILTIN_PRIVATE_H

# include "libft.h"
# include "minishell.h"

void	ft_strcpy(char *dst, const char *src, size_t size);
char	**create_buff(char **map_buff, t_map *map, int *err);
char	**create_valbuf(char **value, t_map *map, int *err);
char	**sort_buff(char **buff, int len, char ***value);
void	delete_buff(char **m, char **v, int length);
int		ft_searchr(char *s, char c);
void	ft_strcpy(char *dst, const char *src, size_t size);
int		check_arg(char **av, int *check, int *option);
int		one_minus(char *cwd, t_shell_data *data, char *new_cwd);

#endif // !BUILTIN_PRIVATE_H
