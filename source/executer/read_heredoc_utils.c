/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:01:44 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/31 16:05:51 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

char	*generate_file_name(char *pattenr, char *stop_word)
{
	char			*tmp1;
	char			*tmp2;
	char			*file_name;
	static uint8_t	i = 0;

	tmp1 = ft_strjoin(pattenr, stop_word);
	if (!tmp1)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, "_");
	free (tmp1);
	if (!tmp2)
		return (NULL);
	file_name = ft_strjoin(tmp2, ft_itoa(i++));
	free(tmp2);
	return (file_name);
}
