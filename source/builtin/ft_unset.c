/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:59:03 by medric            #+#    #+#             */
/*   Updated: 2022/08/02 18:40:41 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"

int	ft_unset(t_shell_data *data, t_vector *cmd)
{
	map_delete(data->env_map, cmd->data[1]);
	if (vector_delete(data->env_vector, cmd->data[1]) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
