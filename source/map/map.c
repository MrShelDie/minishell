/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:56:43 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/20 15:58:59 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_private.h"
#include "libft.h"
#include <stdlib.h>

/**
 * @brief Allocates memory and initializes the map.
 * 
 * @return If successful pointer to the created map is returned.
 * 		   In case of a memory allocation error, the NULL value is returned.
 */
t_map	*map_create(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->head = NULL;
	map->length = 0;
	return (map);
}

/**
 * @brief Frees up memory allocated for the map and memory
 * 		  allocated for data stored in the map.
 * 
 * @param map Pointer to the map.
 */
void	map_destroy(t_map *map)
{
	t_map_node	*current;
	t_map_node	*next;

	if (!map)
		return ;
	current = map->head;
	while (current)
	{
		next = current->next;
		map_destroy_node(current);
		current = next;
	}
	free(map);
}

/**
 * @brief Adds a copy of key-value pair to the map.
 * 		  If there is a pair in map with a key equivalent to the one passed
 * 		  in the parameter, then the value of this pair will be overwritten
 * 		  with the value passed in the parameter.
 * 
 * @param map Pointer to the map.
 * @param key Key string.
 * @param value Value string.
 * @return If successful, the value 1 is returned.
 * 		   In case of a memory allocation error or if a NULL pointer
 * 		   to map, key or value was passed to the function, the value 0 is returned.
 */
int	map_add(t_map *map, const char *key, const char *value)
{
	t_map_node	**current;
	size_t		key_length;

	if (!map || !key || !value)
		return (FAIL);
	current = &map->head;
	key_length = ft_strlen(key);
	while (*current && ft_strncmp((*current)->key, key, key_length + 1) != 0)
		current = &(*current)->next;
	if (*current)
		return (map_replace_value(*current, value));
	*current = map_crete_node(key, value);
	if (!*current)
		return (FAIL);
	map->length++;
	return (SUCCESS);
}

/**
 * @brief Deletes a key-value pair with a key identical
 * 		  to the one passed in the parameter.
 * 
 * @param map Pointer to the map.
 * @param key Key string.
 */
void	map_delete(t_map *map, const char *key)
{
	t_map_node	**current;
	t_map_node	*next;
	size_t		key_length;

	if (!map || !key)
		return ;
	current = &map->head;
	key_length = ft_strlen(key);
	while (*current && ft_strncmp((*current)->key, key, key_length + 1) != 0)
		current = &(*current)->next;
	if (!*current)
		return ;
	next = (*current)->next;
	map_destroy_node(*current);
	*current = next;
	map->length--;
}

/**
 * @brief Returns the value stored in the map (not a copy) associated
 * 		  with the key passed as a parameter.
 * 
 * @param map Pointer to the map.
 * @param key Key string.
 * @return If successful, pointer to the value string is returned.
 * 		   In case the key could not be found in the map,
 * 		   the NULL value is returned.
 */
const char	*map_get(t_map *map, const char *key)
{
	t_map_node	*current;
	size_t		key_length;

	if (!map || !key)
		return (NULL);
	current = map->head;
	key_length = ft_strlen(key);
	while (current && ft_strncmp(current->key, key, key_length + 1) != 0)
		current = current->next;
	if (!current)
		return (NULL);
	return (current->value);
}
