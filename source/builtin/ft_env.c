/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:35:43 by medric            #+#    #+#             */
/*   Updated: 2022/08/05 18:10:58 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"
#include <stdlib.h>

int	ft_env(t_shell_data *data, t_vector *cmd)
{
	t_map_node	*map;

	(void)cmd;
	map = data->env_map->head;
	while (map)
	{
		ft_putstr_fd(map->key, 1);
		if (map->key && map->value == NULL)
			return (EXIT_FAILURE);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(map->value, 1);
		ft_putstr_fd("\n", 1);
		map = map->next;
	}
	return (EXIT_SUCCESS);
}
