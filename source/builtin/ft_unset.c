/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:59:03 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 17:40:22 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include "../../include/builtins.h"
#include "../../include/minishell.h"

int	ft_unset(char **av, t_shell_data *data)
{
	map_delete(data->env_map, av[1]);
	if (vector_delete(data->env_vector, av[1]) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
