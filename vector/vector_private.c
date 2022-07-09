/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_private.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:18:37 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/09 21:16:06 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_private.h"
#include "libft.h"
#include <stdlib.h>

/**
 * @brief Finds the length of an array of strings that ends in NULL.
 * 
 * @param data An array of strings that ends in NULL.
 * @return The length of the array.
 * 		   If a NULL pointer is passed to the function,
 * 		   NULL is returned.
 */
size_t	data_length(char *const *data)
{
	size_t	i;

	if (!data)
		return (0);
	i = 0;
	while (data[i])
		i++;
	return (i);
}

/**
 * @brief Copies an array of strings that ends in NULL.
 * 
 * @param data An array of strings that ends in NULL.
 * @return If successful pointer to the array copy returned.
 * 		   In case of a memory allocation error or
 * 		   if a NULL pointer is passed to the function,
 * 		   the NULL pointer is returned.
 */
char	**copy_data(char *const *data)
{
	char	**new_data;
	size_t	length;
	size_t	i;

	if (!data)
		return (NULL);
	length = data_length(data);
	new_data = (char **)malloc(sizeof(char *) * (length + 1));
	if (!new_data)
		return (NULL);
	i = -1;
	while (++i < length)
	{
		new_data[i] = ft_strdup(data[i]);
		if (!new_data[i])
		{
			while (--i > 0)
				free(new_data[i]);
			free(new_data[0]);
			free(new_data);
			return (NULL);
		}
	}
	new_data[i] = NULL;
	return (new_data);
}

/**
 * @brief Gets the address of the element in vector with the same value as
 * 		  the one passed in the parameter.
 * 
 * @param data_start An array of strings to search for the element.
 * @param value The value by which the element will be searched.
 * @return The address of the element in the list.
 * 		   If the element is not found or any function parameter is NULL,
 * 		   NULL is returned.
 */
char	**get_value_address(char **data_start, const char *value)
{
	char	**value_address_in_vector;
	size_t	value_length;

	if (!data_start || !value)
		return (NULL);
	value_length = ft_strlen(value);
	value_address_in_vector = data_start;
	while (*value_address_in_vector && ft_strncmp(*value_address_in_vector,
			value, value_length + 1) != 0)
		++value_address_in_vector;
	if (!*value_address_in_vector)
		return (NULL);
	return (value_address_in_vector);
}
