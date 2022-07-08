/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:42:24 by gannemar          #+#    #+#             */
/*   Updated: 2021/10/15 19:42:24 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_trim_front(char const *str, char const *set)
{
	char const	*set_symb;

	while (*str)
	{
		set_symb = set;
		while (*set_symb)
		{
			if ((unsigned char)*str == (unsigned char)*set_symb)
			{
				str++;
				break ;
			}
			set_symb++;
		}
		if (*set_symb == '\0')
			break ;
	}
	return ((char *)str);
}

static char	*ft_trim_back(char const *str, char const *set)
{
	char const	*str_end;
	char const	*set_symb;

	str_end = str + ft_strlen(str) - 1;
	while (str_end >= str)
	{
		set_symb = set;
		while (*set_symb)
		{
			if ((unsigned char)*str_end == (unsigned char)*set_symb)
			{
				str_end--;
				break ;
			}
			set_symb++;
		}
		if (*set_symb == '\0')
			break ;
	}
	return ((char *)++str_end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_start;
	char	*trimmed_end;
	char	*trimmed_str;
	size_t	trimmed_len;

	if (!s1 || !set)
		return (NULL);
	trimmed_start = ft_trim_front(s1, set);
	trimmed_end = ft_trim_back(s1, set);
	if (trimmed_end >= trimmed_start)
		trimmed_len = trimmed_end - trimmed_start + 1;
	else
		trimmed_len = 1;
	trimmed_str = (char *)malloc(sizeof(char) * trimmed_len);
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, trimmed_start, trimmed_len);
	return (trimmed_str);
}
