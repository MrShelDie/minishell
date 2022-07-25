/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:59:27 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/25 17:12:36 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_PRIVATE_H
# define EXPAND_PRIVATE_H

# include "minishell.h"
# include <stddef.h>
# include <stdbool.h>

typedef	struct	s_asterisk_map
{
	bool	*array;
	bool	contains_wildcard;
	size_t	size;
}	t_asterisk_map;

typedef struct	s_quote
{
	char	symbol;
	bool	inside;
}	t_quote;

int		fill_asterisk_map(t_asterisk_map *asterisk_map, const char *str);
void	free_asterisk_map(t_asterisk_map *asterisk_map);

bool	check_expansion(const char *str);

int		replace_with_expanded_str(
			const t_map *env_map, const char **str);

int		append_regular_str(char **dst, const char **src);
int		append_expanded_str(
			const t_map *env_map, char **dst, const char **src);

int		insert_matched_wildcard_arg_list(const t_shell_data *shell_data,
			t_arg_list **current, t_arg_list *next);
int		replace_matched_redir(
			const t_shell_data *shell_data, const char **pattern);

#endif
