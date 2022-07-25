/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:59:47 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/25 20:37:16 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_private.h"
#include <stdlib.h>

typedef	struct	s_matched
{
	char	**array;
	size_t	size;
}	t_matched;

static t_arg_list	*get_matched_list(const char *pattern)
{
	

	
}

int	insert_matched_wildcard_arg_list(
	const t_shell_data *shell_data, t_arg_list **current, t_arg_list *next)
{
	t_arg_list	*expanded_list;

	expanded_list = get_matched_list((*current)->content);
	if (!expanded_list)
		return (FAIL);
	ft_lstdelone(*current, free);
	*current = expanded_list;
	while (*current)
		current = &(*current)->next;
	(*current)->next = next;
	return (SUCCESS);
}
