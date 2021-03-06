/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:14:06 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/19 14:45:02 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_private.h"
#include "libft.h"
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
 * @brief Allocates memory and initializes the vector
 * 		  with a copy of the data parameter.
 * 
 * @param data An array of words that ends with a NULL value.
 * @return If successful pointer to the created vector is returned.
 * 		   In case of a memory allocation error or if a NULL pointer
 * 		   to data parameter was passed to the function, the NULL value is returned.
 */
t_vector	*vector_create_copy(char *const *data)
{
	t_vector	*vector;

	if (!data)
		return (NULL);
	vector = (t_vector *)malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->data = copy_data(data);
	if (!vector->data)
	{
		free(vector);
		return (NULL);
	}
	vector->length = data_length(data);
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
		while (++i < vector->length)
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

	if (!vector)
		return (FAIL);
	value_copy = ft_strdup(value);
	if (value && !value_copy)
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
