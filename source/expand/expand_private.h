/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:59:27 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/05 15:58:15 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_PRIVATE_H
# define EXPAND_PRIVATE_H

# include <dirent.h>
# include <sys/types.h>

# include "minishell.h"
# include "expand.h"

typedef struct s_asterisk
{
	bool	*array;
	bool	contains_wildcard;
	size_t	size;
}	t_asterisk;

typedef struct s_quote
{
	char	symbol;
	bool	inside;
}	t_quote;

typedef struct s_matched
{
	char	**words;
	size_t	count;
}	t_matched;

typedef struct s_matrix
{
	bool	**array;
	char	*str;
	char	*pattern;
	size_t	str_len;
	size_t	pattern_len;
	bool	*asterisk_map;
}	t_matrix;

typedef struct dirent	t_dirent;

int			fill_asterisk_map(t_asterisk *asterisk_map, const char *str);
void		free_asterisk_map(t_asterisk *asterisk_map);

bool		check_expansion(const char *str);

int			replace_with_expanded_str(
				const t_shell_data *shell_data, void **str);

int			append_regular_str(char **dst, char **src);
int			append_expanded_str(
				const t_shell_data *shell_data, char **dst, char **src);

int			append_substr(char **dst, const char *src, size_t len);

const char	*get_variable_value(
				const t_shell_data *shell_data, const char *str);
size_t		get_variable_length(const char *str);

int			insert_matched_wildcard_arg_list(
				t_arg_list **current, t_arg_list *next, bool *asterisk_map);
int			replace_matched_redir(void **redir_value, bool *asterisk_map);

int			get_matched_dir_name_list(t_list **matched_dir_list,
				const char *pattern, bool *asterisk_map);

int			append_exposed_dir_name_to_list(
				t_list **matched_dir_list, DIR *dir, const t_dirent *dirent);
int			append_hidden_dir_name_to_list(
				t_list **matched_dir_list, DIR *dir, const t_dirent *dirent);

bool		is_matched(const char *str, const char *pattern,
				bool *asterisk, int *err);

int			init_matrix(t_matrix *matrix, const char *str,
				const char *pattern, bool *asterisk_map);
void		fill_matrix(t_matrix matrix);
void		destroy_matrix(t_matrix *matrix);

#endif
