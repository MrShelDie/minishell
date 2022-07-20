/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:59:03 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 18:14:30 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "minishell.h"

int	ft_unset(char **av, t_shell_data *data)
{
	map_delete(data->env_map, av[1]);
	if (vector_delete(data->env_vector, av[1]) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
