/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_shell_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:55:01 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 20:09:27 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	destroy_shell_data(t_shell_data *shell_data)
{
	if (!shell_data)
		return ;
	map_destroy(shell_data->env_map);
	vector_destroy(shell_data->env_vector);
	ft_bzero(shell_data, sizeof(t_shell_data));
}
