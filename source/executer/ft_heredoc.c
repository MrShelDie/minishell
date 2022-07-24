/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:58:36 by medric            #+#    #+#             */
/*   Updated: 2022/07/20 18:55:52 by gannemar         ###   ########.fr       */
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

/**
 * @brief In this function we delete buffers in our heredoc function, which we create
 * @param av buffer, which we want to destroy
 */
void	delete_buff_here(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	av = NULL;
}

/**
 * @brief In part_one we write envp-data, if we don't meeting special symbols for envp-data
 * @param env  our map envp
 * @param path spliting massive buffer, which we may split if meet special case  
 * @param fd file fd's
 * @return int length massiv envp-value for to move in basic arguments in our buffer
 */
int	part_one(t_map *env, char **path, int fd)
{
	if (map_get(env, path[1]) != NULL)
	{
		write(fd, map_get(env, path[1]), ft_strlen(map_get(env, path[1])));
		delete_buff_here(path);
	}
	return (ft_strlen(path[1]));
}

/**
 * @brief In part_two we write envp-data, if was created massiv this key-map's data \n
 * and after envp-keys, we have next join this data diffrent arguments  
 * @param env our map envp
 * @param path  spliting massive buffer, which we may split if meet special case  
 * @param fd file fd's
 * @param new_path massiv, which spliting from path, because we meet next join with him argument, for example \n
 * aaa($PWD)aaa, "aaa" after "(" this next join with him argument
 * @return int length massiv envp-value for to move in basic arguments in our buffer
 */
int	part_two(t_map *env, char **path, int fd, char **new_path)
{
	if (map_get(env, new_path[0]) != NULL)
	{
		write(fd, map_get(env, new_path[0]), ft_strlen(map_get(env, new_path[0])));
		delete_buff_here(new_path);
		delete_buff_here(path);
	}
	return (ft_strlen(new_path[0]));
}

/**
 * @brief In this (void)unction we check special symbols for  writting in file - envp data, if we want this
 * @param env our map envp
 * @param buff buffer data from readline from heredoc
 * @param i iterator from check special symbols
 * @param fd file fd's
 * @param path spliting massive buffer, which we may split if meet special case  
 */
void	exec_case_here(t_map *env, char *buff, int *i, int fd, char **path)
{
	char	**new_path;
	int		j;

	new_path = NULL;
	j = (*i);
	while (buff[j])
	{
		if ((buff[j] >= 33 && buff[j] <= 47) || 
			(buff[j] >= 58 && buff[j] <= 64) || 
			(buff[j] >= 91 && buff[j] <= 94) ||
			(buff[j] == '}'))
			new_path = ft_split(path[1], buff[j]);
		j++;
	}
	if (new_path == NULL)
		(*i) += part_one(env, path, fd);
	else
		(*i) += part_two(env, path, fd, new_path);
}

/**
 * @brief This function check keys in our envp'map and stop writting in file, if 
 * we meet stop_word, special case is '$' and, if we meet thois case, we create buff_arg
 * which come to our function from readline from heredoc
 * @param env our map envp
 * @param stop_word 
 * @param buff buffer data from readline from heredoc
 * @param flg flag from stop write in file, if we meet stop_word 
 * @param fd file fd's
 */
void	exec_write_here(t_map *env, const char *stop_word, char *buff, int *flg, int fd)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	if (ft_strcmp(buff, stop_word) == 0)
		(*flg) = false;
	while (buff[i])
	{
		if ((*flg) == false)
			break ;
		if (buff[i] == '$')
		{
			path = ft_split(buff, '$');
			if (i != 0 && path[1] != NULL)
				exec_case_here(env, buff, &i, fd, path);
			else if (path[0] != NULL && i == 0)
			{
				i += ft_strlen(path[0]);
				write(fd, map_get(env, path[0]), ft_strlen(map_get(env, path[0])));
				delete_buff_here(path);
			}
		}
		else
			write(fd, &buff[i], 1);
		i++;
	}
}

/**
 * @brief Create a heredoc object, we create file in our directory, and to start parse
 * diffrent cases
 * @param env our map envp
 * @param stop_word 
 * @return int file fd 
 */
int	create_heredoc(t_map *env, const char *stop_word)
{
	char	*input_here;
	char	**buff;
	int		fd;
	int		flg;

	flg = true;
	buff = NULL;
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd == -1)
			return (-1);
	while (flg == true)
	{
		input_here = readline("> ");
		buff = ft_split(input_here, ' ');
		while (*buff)
		{
			exec_write_here(env, stop_word, (*buff), &flg, fd);
			buff++;
			if ((*buff) == NULL && flg == true)
				write(fd, "\n", 1);
		}
		delete_buff_here(buff);
	}
	close(fd);
	return (fd);
}
