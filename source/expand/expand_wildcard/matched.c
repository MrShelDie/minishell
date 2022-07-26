/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matched.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:20:57 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/26 22:21:15 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_private.h"
#include <stdlib.h>

void	destroy_matched(t_matched *matched)
{
	size_t	i;

	if (matched->words)
	{
		i = -1;
		while (++i < matched->count)
			free(matched->words[i]);
		free(matched->words);
	}
	ft_bzero(matched, sizeof(t_matched));
}
