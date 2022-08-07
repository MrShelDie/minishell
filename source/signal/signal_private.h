/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:38:42 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/07 21:39:53 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_PRIVATE_H
# define SIGNAL_PRIVATE_H

# include "shell_signal.h"

void	sigquit_fork_handler(int signum);
void	sigint_fork_handler(int signum);

#endif // !SIGNAL_PRIVATE_H
