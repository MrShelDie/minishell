/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:35:43 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 17:39:51 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/builtins.h"
#include "../../include/minishell.h"

int	ft_env(t_map_node *map)
{
	while (map)
	{
		ft_putstr_fd(map->key, 1);
		if (map->key && map->value == NULL)
			return (FAIL);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(map->value, 1);
		ft_putstr_fd("\n", 1);
		map = map->next;
	}
	return (SUCCESS);
}
