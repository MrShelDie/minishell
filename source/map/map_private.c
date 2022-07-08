/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_private.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:33:14 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/07 20:54:07 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_private.h"
#include "libft.h"
#include <stdlib.h>

/**
 * @brief Replaces the data stored in the node with a copy of the data
 * 		  passed as a parameter. The memory allocated for old data in
 * 		  the node is released.
 * 
 * @param node pointer to the node
 * @param value pointer to the value string
 * @return If successful, the value 1 is returned.
 * 		   In case of a memory allocation error or in case of passing
 * 		   NULL pointers to the function, the function will return 0.
 */
int	map_replace_value(t_map_node *node, const char *value)
{
	char	*value_copy;

	if (!node || !value)
		return (FAIL);
	value_copy = ft_strdup(value);
	if (!value_copy)
		return (FAIL);
	free(node->value);
	node->value = value_copy;
	return (SUCCESS);
}

/**
 * @brief Allocates memory for the node and initializes it
 * 		  with copies of the key and value passed as parameters.
 * 
 * @param key Key string.
 * @param value Value string.
 * @return If successful, a pointer to the created node is returned.
 * 		   In case of a memory allocation error or if a NULL pointer
 * 		   to map, key or value was passed to the function,
 * 		   the NULL value is returned.
 */
t_map_node	*map_crete_node(const char *key, const char *value)
{
	t_map_node	*node;

	if (!key || !value)
		return (NULL);
	node = (t_map_node *)malloc(sizeof(t_map_node));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (FAIL);
	}
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free(node->key);
		free(node);
		return (FAIL);
	}
	node->next = NULL;
	return (node);
}

/**
 * @brief Frees up the memory allocated for the node and the data stored in it.
 * 
 * @param node Pointer to the node.
 */
void	map_destroy_node(t_map_node *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}
