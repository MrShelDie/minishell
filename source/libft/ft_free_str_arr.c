/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:27:02 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/05 14:29:33 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_str_arr(char **str_arr)
{
	size_t	i;

	if (!str_arr)
		return ;
	i = -1;
	while (str_arr[++i])
		free(str_arr[i]);
	free(str_arr[i]);
	free(str_arr);
}
