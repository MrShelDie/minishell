/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:59:47 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/27 21:00:15 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand_private.h"
#include <stdlib.h>

int	insert_matched_wildcard_arg_list(t_arg_list **current, t_arg_list *next)
{
	t_list	*matched_dir_list;

	if (!get_matched_dir_name_list(&matched_dir_list, (*current)->content))
		return (FAIL);
	if (!matched_dir_list)
		return (SUCCESS);
	ft_lstdelone(*current, free);
	*current = matched_dir_list;
	while (*current)
		current = &(*current)->next;
	(*current)->next = next;
	return (SUCCESS);
}
