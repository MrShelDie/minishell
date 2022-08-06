/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:09:27 by medric            #+#    #+#             */
/*   Updated: 2022/08/06 20:58:49 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"
#include <stdlib.h>

static size_t	get_index_of_first_not_empty(
	t_vector *argv, size_t start_index)
{
	size_t	i;

	i = start_index;
	while (i < argv->length && argv->data[i][0] == '\0')
		++i;
	return (i);
}

static size_t	get_index_of_last_not_empty(
	t_vector *argv, size_t start_index
)
{
	size_t	i;

	i = start_index;
	while (argv->data[i][0] == '\0')
		--i;
	return (i);
}

static void	print_args(t_vector *argv, size_t start_index)
{
	size_t	i;
	size_t	last_not_empty_idx;

	i = get_index_of_first_not_empty(argv, start_index);
	last_not_empty_idx = get_index_of_last_not_empty(argv, argv->length - 1);
	if (i > last_not_empty_idx)
		return ;
	while (i < last_not_empty_idx)
	{
		ft_putstr_fd(argv->data[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		++i;
	}
	ft_putstr_fd(argv->data[i], STDOUT_FILENO);
}

static bool	check_options(t_vector *argv, size_t argnum)
{
	return (argnum < argv->length
		&& ft_strncmp(argv->data[argnum], "-n", 2) == 0
	);
}

int	ft_echo(t_shell_data *data, t_vector *argv)
{
	bool	with_option;
	size_t	i;

	(void)data;
	with_option = false;
	i = 1;
	if (check_options(argv, i))
	{
		with_option = true;
		i++;
	}
	print_args(argv, i);
	if (!with_option || argv->length == 2)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
