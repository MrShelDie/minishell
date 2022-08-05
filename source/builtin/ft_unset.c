/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:59:03 by medric            #+#    #+#             */
/*   Updated: 2022/08/05 18:12:24 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"
#include <stdlib.h>

int	ft_unset(t_shell_data *data, t_vector *cmd)
{
	map_delete(data->env_map, cmd->data[1]);
	if (vector_delete(data->env_vector, cmd->data[1]) == FAIL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
