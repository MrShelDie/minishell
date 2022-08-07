/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:38:04 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/07 21:40:50 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	sigint_fork_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
}

void	sigquit_fork_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit: 3\n", 1);
}
