/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 01:19:49 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 00:28:45 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "parser_private.h"
#include "libft.h"

static void	putstr_fd_in_quotes(const char *str, int fd)
{
	ft_putchar_fd('\'', fd);
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\'', fd);
}

void	unexpected_token_error(t_token *token, size_t recursion_level)
{
	ft_putstr_fd(SYNTAX_ERR_MSG, STDERR_FILENO);
	if (token->id == TOKEN_PIPE)
		ft_putstr_fd("'|'", STDERR_FILENO);
	else if (token->id == TOKEN_ANG_BR_L)
		ft_putstr_fd("'<'", STDERR_FILENO);
	else if (token->id == TOKEN_ANG_BR_R)
		ft_putstr_fd("'>'", STDERR_FILENO);
	else if (token->id == TOKEN_D_ANG_BR_L)
		ft_putstr_fd("'<<'", STDERR_FILENO);
	else if (token->id == TOKEN_D_ANG_BR_R)
		ft_putstr_fd("'>>'", STDERR_FILENO);
	else if (token->id == TOKEN_AND)
		ft_putstr_fd("'&&'", STDERR_FILENO);
	else if (token->id == TOKEN_OR)
		ft_putstr_fd("'||'", STDERR_FILENO);
	else if (token->id == TOKEN_PAR_L)
		ft_putstr_fd("'('", STDERR_FILENO);
	else if (token->id == TOKEN_PAR_R
		|| (token->id == TOKEN_NEW_LINE && recursion_level > 0))
		ft_putstr_fd("')'", STDERR_FILENO);
	else if (token->id == TOKEN_NEW_LINE && recursion_level == 0)
		ft_putstr_fd("'newline'", STDERR_FILENO);
	else
		putstr_fd_in_quotes(token->value, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
