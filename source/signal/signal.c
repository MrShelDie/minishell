/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:02:02 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/05 20:09:25 by gannemar         ###   ########.fr       */
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

#include "libft.h"
#include "shell_signal.h"
#include "shell_error.h"
#include "minishell.h"

void	set_interactive_mode_signals(void)
{
	signal(SIGINT, newline_sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_fork_handler(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', 2);
}

void	sigquit_fork_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit: 3\n", 2);
}

void	set_fork_signals(void)
{
	signal(SIGINT, sigint_fork_handler);
	signal(SIGQUIT, sigquit_fork_handler);
}

void	set_ignore_sigint(void)
{
	signal(SIGINT, SIG_IGN);
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
