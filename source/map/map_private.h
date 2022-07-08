/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_private.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:32:18 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/07 20:51:15 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PRIVATE_H
# define MAP_PRIVATE_H

# define SUCCESS 1
# define FAIL 0

# include "map.h"

t_map_node	*map_crete_node(const char *key, const char *value);
void		map_destroy_node(t_map_node *node);

int			map_replace_value(t_map_node *node, const char *value);

#endif // !MAP_PRIVATE_H
