/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:59:47 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/26 22:21:08 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_private.h"
#include <stdlib.h>

static int	alloc_matched_list(
	t_arg_list **matched_list, size_t matched_word_count)
{
	t_arg_list	*new;
	size_t		i;

	i = -1;
	while (++i < matched_word_count)
	{
		new = ft_lstnew(NULL);
		if (!new)
		{
			ft_lstclear(matched_list, free);
			return (FAIL);
		}
		ft_lstadd_back(matched_list, new);
	}
	return (SUCCESS);
}

static int	init_matched_list(t_arg_list **matched_list, const char *pattern)
{
	t_matched	matched;

	ft_bzero(&matched, sizeof(t_matched));
	if (!fill_matched(&matched, pattern)
		|| !alloc_matched_list(matched_list, matched.count))
	{
		destroy_matched(&matched);
		return (FAIL);
	}
	fill_matched_list(matched_list, matched.words);
	free(matched.words);
	return (SUCCESS);
}

int	insert_matched_wildcard_arg_list(t_arg_list **current, t_arg_list *next)
{
	t_arg_list	*matched_list;

	if (!init_matched_list(&matched_list, (*current)->content))
		return (FAIL);
	ft_lstdelone(*current, free);
	*current = matched_list;
	while (*current)
		current = &(*current)->next;
	(*current)->next = next;
	return (SUCCESS);
}
