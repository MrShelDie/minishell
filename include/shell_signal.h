/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:03:19 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/02 14:46:46 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_SIGNAL_H
# define SHELL_SIGNAL_H

typedef void	(*sighandler_t)(int);

void	set_signals(void);
void	disable_display_control_symbols(void);
void	newline_sig_handler(int signum);

#endif
