/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:05:30 by gannemar          #+#    #+#             */
/*   Updated: 2021/11/13 15:05:32 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl_list	*new_list(void)
{
	t_gnl_list	*new;

	new = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (!new)
		return (NULL);
	new->len = 0;
	new->next = NULL;
	return (new);
}

t_gnl_list	*push_back_list(t_gnl_list *last)
{
	if (!last)
		return (NULL);
	last->next = new_list();
	return (last->next);
}

void	free_list_elem(t_gnl_list *elem)
{
	if (!elem)
		return ;
	free(elem);
}

void	free_list(t_gnl_list **list)
{
	t_gnl_list	*current;
	t_gnl_list	*prev;

	if (!*list)
		return ;
	current = *list;
	while (current->next != NULL)
	{
		prev = current;
		current = current->next;
		free_list_elem(prev);
	}
	free_list_elem(current);
	*list = NULL;
}
