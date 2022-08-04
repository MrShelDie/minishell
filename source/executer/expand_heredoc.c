/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/08/04 20:21:28 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"
#include "executer_private.h"
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

static char	*get_stop_word(const char *str)
{
	char	**words;
	char	*stop_word;

	words = ft_split(str, '_');
	if (!words)
	{
		print_error(strerror(errno));
		return (NULL);
	}
	stop_word = ft_strdup(words[1]);
	free_words(words);
	return (stop_word);
}

static int	expand_var(
	t_map *env, int old_fd, int new_fd, const char *stop_word)
{
	char	*input_here;

	while (true)
	{
		input_here = get_next_line(old_fd);
		if (!input_here)
		{
			print_error(strerror(errno));
			return (FAIL);
		}
		if (ft_strcmp(input_here, stop_word) == 0)
			break ;
		if (!replace_expanded_var(env, &input_here))
		{
			free(input_here);
			return (FAIL);
		}
		ft_putstr_fd(input_here, new_fd);
		free(input_here);
	}
	free(input_here);
	return (SUCCESS);
}

int	expand_var_in_heredoc(t_map *env, void **file_name)
{
	char	*stop_word;
	char	*new_file_name;
	int		old_fd;
	int		new_fd;
	int		exit_status;

	stop_word = get_stop_word(*file_name);
	if (!stop_word)
	{
		print_error(strerror(errno));
		return (FAIL);
	}
	new_file_name = open_files(*file_name, &old_fd, &new_fd);
	if (!new_file_name)
	{
		free(stop_word);
		return (FAIL);
	}
	free(*file_name);
	*file_name = new_file_name;
	exit_status = expand_var(env, old_fd, new_fd, stop_word);
	free(stop_word);
	close(old_fd);
	close(new_fd);
	return (exit_status);
}
