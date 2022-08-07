/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_private.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:51:16 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/07 20:58:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PRIVATE_H
# define MINISHELL_PRIVATE_H

# include "minishell.h"

int		increase_shlvl_in_map_and_vector(t_map *map, t_vector *vector);
int		replace_string_in_vector_by_key(
			t_vector *vector, const char *key, const char *value);

int		parse_env_to_map(t_map *map, char *const *envp);

#endif
