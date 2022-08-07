/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_create_from.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:09:26 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/07 17:28:05 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_private.h"
#include <stdlib.h>

/**
 * @brief Allocates memory and initializes the vector
 * 		  with a copy of the array parameter.
 * 
 * @param array An array of words that ends with a NULL value.
 * @return If successful pointer to the created vector is returned.
 * 		   In case of a memory allocation error or if a NULL pointer to array
 * 		   parameter was passed to the function, the NULL value is returned.
 */
t_vector	*vector_create_from_array(char *const *array)
{
	t_vector	*vector;

	if (!array)
		return (NULL);
	vector = (t_vector *)malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->data = copy_data(array);
	if (!vector->data)
	{
		free(vector);
		return (NULL);
	}
	vector->length = data_length(vector->data);
	return (vector);
}

t_vector	*vector_create_from_list(const t_list *list)
{
	t_vector	*vector;
	size_t		i;

	vector = (t_vector *)ft_calloc(1, sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->length = ft_lstsize(list);
	vector->data = (char **)ft_calloc(vector->length + 1, sizeof(char *));
	vector->data[vector->length] = NULL;
	i = 0;
	while (list)
	{
		vector->data[i] = ft_strdup(list->content);
		if (!vector->data[i++])
		{
			vector_destroy(vector);
			return (NULL);
		}
		list = list->next;
	}
	return (vector);
}
