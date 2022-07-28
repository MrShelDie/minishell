/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_matched.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:42:06 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/28 20:48:08 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"

bool	is_matched(const char *str, const char *pattern,
	bool *asterisk_map, int *err)
{
	t_matrix	matrix;
	bool		result;

	if (!init_matrix(&matrix, str, pattern, asterisk_map))
	{
		*err = FAIL;
		return (false);
	}
	fill_matrix(matrix);
	result = matrix.array[matrix.str_len - 1][matrix.pattern_len - 1];
	destroy_matrix(&matrix);
	return (result);
}
