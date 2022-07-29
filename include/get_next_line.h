/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:05:44 by gannemar          #+#    #+#             */
/*   Updated: 2021/11/13 15:33:01 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_buff
{
	char	arr[BUFFER_SIZE];
	size_t	next_char_idx;
	ssize_t	readed_left;
}	t_buff;

typedef struct s_gnl_list
{
	char			arr[BUFFER_SIZE];
	size_t			len;
	struct s_gnl_list	*next;
}	t_gnl_list;

typedef struct s_result
{
	char	*arr;
	size_t	size;
}	t_result;

t_gnl_list	*new_list(void);
void		free_list_elem(t_gnl_list *elem);
t_gnl_list	*push_back_list(t_gnl_list *elem);
void		free_list(t_gnl_list **list);
char		*get_next_line(int fd);

#endif