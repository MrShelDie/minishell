/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:13:43 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/09 21:12:10 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stddef.h>

/**
 * @brief A dynamic array of strings that ends with a null pointer.
 */
typedef struct s_vector
{
	char	**data;
	size_t	length;
}	t_vector;

t_vector	*vector_create(void);
t_vector	*vector_create_copy(char *const *data);
void		vector_destroy(t_vector *vector);

int			vector_add(t_vector *vector, const char *value);
int			vector_delete(t_vector *vector, const char *value);

#endif // !VECTOR_H
