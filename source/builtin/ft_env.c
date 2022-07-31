/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:35:43 by medric            #+#    #+#             */
/*   Updated: 2022/07/31 21:10:16 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"

int	ft_env(t_shell_data *data, char **argv)
{
	t_map_node	*map;

	(void)argv;
	map = data->env_map->head;
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
