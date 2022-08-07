/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase_shlvl_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:45:16 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/07 22:18:30 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell_private.h"
#include "libft.h"

/* Returns false in case of a memory allocation error */
static bool	check_key_in_string(const char *key, const char *string)
{
	char	**words;
	bool	result;

	words = ft_split(string, '=');
	if (!words)
		return (false);
	result = ft_strncmp(words[0], key, ft_strlen(key) + 1) == 0;
	ft_free_str_arr(words);
	return (result);
}

static char	*create_string_by_key_and_value(const char *key, const char *value)
{
	char	*new_string;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (FAIL);
	new_string = ft_strjoin(temp, value);
	free(temp);
	return (new_string);
}

/*
** Returns an index equal to the length of the vector
** if a string with this key is not found.
*/
size_t	vector_get_index_by_key(t_vector *vector, const char *key)
{
	size_t	i;
	char	**fields;

	fields = vector->data;
	i = -1;
	while (++i < vector->length)
	{
		if (check_key_in_string(key, fields[i]))
			break ;
	}
	return (i);
}

int	replace_string_in_vector_by_key(
	t_vector *vector, const char *key, const char *value)
{
	size_t	string_idx;
	char	*new_string;
	int		add_status;

	string_idx = vector_get_index_by_key(vector, key);
	if (string_idx == vector->length)
		return (FAIL);
	new_string = create_string_by_key_and_value(key, value);
	if (!new_string)
		return (FAIL);
	add_status = vector_insert_at(vector, new_string, string_idx);
	free(new_string);
	return (add_status);
}
