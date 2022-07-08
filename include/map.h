/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:56:52 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/08 17:31:51 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stddef.h>

typedef struct s_map_node
{
	char				*key;
	char				*value;
	struct s_map_node	*next;
}	t_map_node;

/**
 * @brief Key-value association list.
 */
typedef struct s_map
{
	t_map_node	*head;
	size_t		length;
}	t_map;

t_map		*map_create(void);
void		map_destroy(t_map *map);

int			map_add(t_map *map, const char *key, const char *value);
void		map_delete(t_map *map, const char *key);

const char	*map_get(t_map *map, const char *key);

#endif // !MAP_H
