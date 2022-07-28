/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/28 20:22:14 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "minishell.h"
#include "parser.h"
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "get_next_line.h"

int	replace_names_in_heredoc(t_map *env, char **file_name)
{
	char	*input_here;
	char	**stop_word;
	char	*str;
	int		fd;
	int		fd2;

	fd = open(*file_name, O_RDONLY);
	stop_word = ft_split(*file_name, '_');
	unlink(*file_name);
	str = ft_strjoin(*file_name, "_tmp");
	free(*file_name);
	*file_name = str;
	fd2 = open(*file_name, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd2 == -1)
			return (1);
	while (true)
	{
		input_here = get_next_line(fd);
		if (!input_here)
			return (1);
		if (ft_strcmp(input_here, stop_word[0]) == 0)
			break ;
		if (!replace_with_expanded_str(env, &input_here))
		{
			// free data
			return (1);
		}
		ft_putstr_fd(input_here, fd2);
	}
	delete_buff_here(stop_word);
	close(fd);
	close(fd2);
	return (0);
}

/**
 * @brief Create a heredoc object, we create file in our directory, and to start parse
 * diffrent cases
 * @param stop_word 
 * @return int file fd 
 */
int	create_heredoc(char **stop_word)
{
	static int	i = 0;
	char		*input_here;
	char		*str;
	int			fd;

	input_here = ft_strjoin(*stop_word, "_");
	str = ft_strjoin(input_here, ft_itoa(i));
	free(input_here);
	fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd == -1)
			return (1);
	while (true)
	{
		input_here = readline("> ");
		if (!input_here)
			return (1);
		ft_putstr_fd(input_here, fd);
		if (ft_strcmp(input_here, *stop_word) == 0)
			break ;
		ft_putstr_fd("\n", fd);
	}
	close(fd);
	free(*stop_word);
	*stop_word = str;
	++i;
	return (0);
}
