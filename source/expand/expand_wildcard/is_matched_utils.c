/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_matched_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:48:57 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/28 20:46:48 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"
#include <stdlib.h>

static void	destroy_matrix_array(bool **array, size_t i)
{
	while (i-- > 0)
		free(array[i]);
	free(array);
}

static bool	**create_matrix_array(size_t i, size_t j)
{
	bool	**matrix;
	size_t	k;

	matrix = (bool **)malloc(sizeof(bool *) * i);
	if (!matrix)
		return (NULL);
	k = -1;
	while (++k < i)
	{
		matrix[k] = (bool *)ft_calloc(j, sizeof(bool));
		if (!matrix[k])
		{
			destroy_matrix_array(matrix, k);
			return (NULL);
		}
	}
	return (matrix);
}

void	destroy_matrix(t_matrix *matrix)
{
	destroy_matrix_array(matrix->array, matrix->str_len);
	free(matrix->str);
	free(matrix->pattern);
	ft_bzero(matrix, sizeof(t_matrix));
}

int	init_matrix(t_matrix *matrix, const char *str,
	const char *pattern, bool *asterisk_map)
{
	ft_bzero(matrix, sizeof(t_matrix));
	matrix->asterisk_map = asterisk_map;
	matrix->str_len = ft_strlen(str) + 1;
	matrix->pattern_len = ft_strlen(pattern) + 1;
	matrix->array = create_matrix_array(
		matrix->str_len + 1, matrix->pattern_len + 1);
	matrix->str = ft_strjoin(" ", str);
	matrix->pattern = ft_strjoin(" ", pattern);
	if (!matrix->array || !matrix->str || !matrix->pattern)
	{
		destroy_matrix(matrix);
		return (FAIL);
	}
	return (SUCCESS);
}

void	fill_matrix(t_matrix matrix)
{
	size_t	i;
	size_t	j;
	size_t	aster_idx;

	aster_idx = 0;
	matrix.array[0][0] = true;
	i = 0;
	while (++i < matrix.str_len)
	{
		j = 0;
		while (++j < matrix.pattern_len)
		{
			if (matrix.str[i - 1] == matrix.pattern[j - 1])
				matrix.array[i][j] = matrix.array[i - 1][j - 1];
			else if (matrix.pattern[j - 1] == '*'
				&& matrix.asterisk_map[aster_idx])
				matrix.array[i][j] =
					matrix.array[i - 1][j] || matrix.array[i][j - 1]; 
		}
	}
}