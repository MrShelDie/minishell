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

int	builtins(t_shell_data *shell_data, t_vector *cmd)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd->data[i], "echo", 4) == 0)
	{
		i++;
		if (ft_echo(cmd->data, i) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "pwd", 3) == 0)
	{
		i++;
		if (ft_pwd() == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "env", 3) == 0)
	{
		i++;
		if (ft_env(shell_data->env_map->head) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "cd", 2) == 0)
	{
		i++;
		if (ft_cd(cmd->data, shell_data) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "unset", 5) == 0)
	{
		i++;
		if (ft_unset(cmd->data, shell_data) == FAIL)
			return (FAIL);
	}
	else if (ft_strncmp(cmd->data[i], "export", 6) == FAIL)
	{
		if (ft_export(cmd, shell_data) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

// int	execute_pipe_group(t_shell_data *shell_data, t_cmd_list *cmd_list)
// {
// 	if (!create_heredoc(shell_data, ((t_cmd *)(cmd_list->content))->argv))
// 		return (FAIL);
// 	if (!builtins(shell_data, ((t_cmd *)(cmd_list->content))->argv))
// 		return (FAIL);
// 	return (SUCCESS);
// }

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

void	exec_case_here(t_map *env, char *buff, int *i, int fd, char **path)
{
	char	**new_path;
	int		j;

	new_path = NULL;
	j = (*i);
	while (buff[j])
	{
		if (buff[j] == '"' || buff[j] == ')')
			new_path = ft_split(path[1], buff[j]);
		j++;
	}
	if (new_path == NULL)
	{
		(*i) += ft_strlen(path[1]);
		if (map_get(env, path[1]) != NULL)
		{
			write(fd, map_get(env, path[1]), ft_strlen(map_get(env, path[1])));
			delete_buff_here(path);
		}
	}
	else
	{
		(*i) += ft_strlen(new_path[0]);
		if (map_get(env, new_path[0]) != NULL)
		{
			write(fd, map_get(env, new_path[0]), ft_strlen(map_get(env, new_path[0])));
			delete_buff_here(new_path);
			delete_buff_here(path);
		}
	}
}


void	exec_write_here(t_map *env, const char *stop_word, char *buff, int *flg, int fd)
{
	int		i;
	char	**path;
	char	**new_path;

	i = 0;
	path = NULL;
	new_path = NULL;
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
			if ((*buff) == NULL)
				write(fd, "\n", 1);
		}
		delete_buff_here(buff);
	}
	close(fd);
	return (fd);
}

int test_heredoc(t_shell_data *shell_data, t_cmd *cmd)
{
	int	heredoc_fd;

	heredoc_fd = create_heredoc(shell_data->env_map, ((t_redir *)cmd->redir_list->content)->value);
	if (heredoc_fd < 0)
		return (FAIL);
	return (SUCCESS);
}

void	executer(t_shell_data *shell_data, t_parsed_data *parsed_data)
{
	t_pipe_group_list	*pipe_group;
	t_operator_list		*operator;
	int					exit_status;

	pipe_group = parsed_data->pipe_group_list;
	operator = parsed_data->operator_list;
	while (true)
	{
		// TODO PIPE GROUP PREPARE

		//// exit_status = execute_pipe_group(
		//// 		shell_data, (t_cmd_list *)pipe_group->content);
		test_heredoc(shell_data, ((t_cmd_list *)pipe_group->content)->content);
		exit_status = 1;
		pipe_group = pipe_group->next;
		if ((*(t_operator *)operator->content == OP_AND && exit_status != 0)
			|| (*(t_operator *)operator->content == OP_OR && exit_status == 0))
			pipe_group = pipe_group->next;
		if (*(t_operator *)operator->content == OP_NEW_LINE)
			return ;
		operator = operator->next;
	}
}
