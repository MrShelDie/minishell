/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:09:27 by medric            #+#    #+#             */
/*   Updated: 2022/07/31 21:07:26 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_private.h"
#include "minishell.h"

static int	num_args(char **argv)
{
	int	size;

	size = 0;
	while (argv[size])
		size++;
	return (size);
}	

int	ft_echo(t_shell_data *data, char **argv)
{
	int	i;
	int	n_option;

	(void)data;
	i = 1;
	n_option = 0;
	if (num_args(argv) > 1)
	{
		if (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
		{
			n_option = 1;
			i++;
		}
		while (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1] && argv[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
		if (n_option == 0)
			write(1, "\n", 1);
		return (SUCCESS);
	}
	return (FAIL);
}
