/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:03:19 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/05 12:35:14 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_SIGNAL_H
# define SHELL_SIGNAL_H

typedef void	(*t_sighandler)(int);

int		set_interactive_mode_signals(void);
int		set_default_signals(void);
int		set_ignore_sigint(void);
void	disable_display_control_symbols(void);
void	newline_sig_handler(int signum);

#endif
