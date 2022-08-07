/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:14:06 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/07 17:37:43 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_private.h"
#include <stdlib.h>

/**
 * @brief Allocates memory and initializes an empty vector.
 * 
 * @return If successful pointer to the created vector is returned.
 * 		   In case of a memory allocation error, the NULL value is returned.
 */
t_vector	*vector_create(void)
{
	t_vector	*vector;

	vector = (t_vector *)malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->data = (char **)malloc(sizeof(char *));
	if (!vector->data)
	{
		free(vector);
		return (NULL);
	}
	vector->data[0] = NULL;
	vector->length = 0;
	return (vector);
}

/**
 * @brief Frees up memory allocated for the vector and memory
 * 		  allocated for data stored in the vector.
 * 
 * @param vector Pointer to the vector.
 */
void	vector_destroy(t_vector *vector)
{
	size_t	i;

	if (!vector)
		return ;
	if (vector->data)
	{
		i = -1;
		while (++i < vector->length + 1)
			free(vector->data[i]);
		free(vector->data);
	}
	free(vector);
}

/**
 * @brief Adds a copy of value parameter to the vector.
 * 
 * @param vector Pointer to the vector.
 * @param value The string whose copy will be added to the vector.
 * @return If successful, the value 1 is returned.
 * 		   In case of a memory allocation error or if a NULL pointer
 * 		   to vector was passed to the function,
 * 		   the value 0 is returned.
 */
int	vector_add(t_vector *vector, const char *value)
{
	char	*value_copy;
	char	**new_data;
	size_t	i;

	if (!vector || !value)
		return (FAIL);
	value_copy = ft_strdup(value);
	if (!value_copy)
		return (FAIL);
	new_data = malloc(sizeof(char *) * (vector->length + 2));
	if (!new_data)
	{
		free(value_copy);
		return (FAIL);
	}
	i = -1;
	while (++i < vector->length)
		new_data[i] = vector->data[i];
	new_data[i] = value_copy;
	new_data[++i] = NULL;
	free(vector->data);
	vector->data = new_data;
	vector->length++;
	return (SUCCESS);
}

/**
 * @brief Deletes from the vector an element with a value
 * 		  equal to the value passed as a parameter.
 * 
 * @param vector Pointer to the vector.
 * @param value The string whose copy stored in the vector
 * 		  		will be removed from it.
 * @return If successful, or if the string passed to the parameter
 * 		   was not found in the vector the value 1 is returned.
 * 		   In case of a memory allocation error or if a NULL pointer
 * 		   in any of the function parameters was passed,
 * 		   the value 0 is returned.
 */
int	vector_delete(t_vector *vector, const char *value)
{
	char	**new_data;
	char	**value_address_in_vector;
	size_t	i;

	if (!vector || !value)
		return (FAIL);
	value_address_in_vector = get_value_address(vector->data, value);
	if (!value_address_in_vector)
		return (SUCCESS);
	new_data = (char **)malloc(sizeof(char *) * vector->length);
	if (!new_data)
		return (FAIL);
	i = -1;
	while (vector->data + (++i) < value_address_in_vector)
		new_data[i] = vector->data[i];
	free(vector->data[i]);
	while (++i < vector->length)
		new_data[i - 1] = vector->data[i];
	new_data[i - 1] = NULL;
	free(vector->data);
	vector->data = new_data;
	vector->length--;
	return (SUCCESS);
}

/**
 * @brief Inserts a copy of value parameter to the index position.
 * 
 * @param vector Pointer to the vector.
 * @param value The string to be inserted into the vector.
 * @param index Index of the position where the inserted data will be.
 * @return If successful, the value 1 is returned.
 *		In case of a memory allocation error,
 *		if a NULL pointer to vector was passed to the function, or
 *		if the index exceeds the length of the vector
 *  	the value 0 is returned.
 */
int	vector_insert_at(t_vector *vector, const char *value, size_t index)
{
	char	*value_copy;

	if (!vector)
		return (FAIL);
	if (index > vector->length)
		return (FAIL);
	value_copy = ft_strdup(value);
	if (!value_copy)
		return (FAIL);
	free(vector->data[index]);
	vector->data[index] = value_copy;
	return (SUCCESS);
}
