/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:02:02 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/02 18:17:32 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "shell_signal.h"
#include "libft.h"
#include "error.h"

void	set_signals(void)
{
	if (signal(SIGINT, newline_sig_handler) == SIG_ERR)
		exit_with_error_msg(strerror(errno), EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit_with_error_msg(strerror(errno), EXIT_FAILURE);
}

void	disable_display_control_symbols(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit_with_error_msg(strerror(errno), EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, 0, &term) == -1)
		exit_with_error_msg(strerror(errno), EXIT_FAILURE);
}

void	newline_sig_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 1);
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}
