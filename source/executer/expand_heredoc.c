/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/31 17:50:00 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"
#include "executer_private.h"
#include <fcntl.h>
#include <stdlib.h>

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
		return (NULL);
	stop_word = ft_strdup(words[1]);
	free_words(words);
	return (stop_word);
}

static char	*open_files(const char *old_file_name, int *old_fd, int *new_fd)
{
	char	*new_file_name;

	new_file_name = ft_strjoin(old_file_name, "_exp");
	if (!new_file_name)
		return (NULL);
	*old_fd = open(old_file_name, O_RDONLY);
	if (*old_fd < 0)
	{
		free(new_file_name);
		return (NULL);
	}
	unlink(old_file_name);
	*new_fd = open(new_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (*new_fd < 0)
	{
		close(*old_fd);
		free(new_file_name);
		return (NULL);
	}
	return (new_file_name);
}

static int	expand_var(
	t_map *env, int old_fd, int new_fd, const char *stop_word)
{
	char	*input_here;

	while (true)
	{
		input_here = get_next_line(old_fd);
		if (!input_here)
			return (FAIL);
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
		return (FAIL);
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
