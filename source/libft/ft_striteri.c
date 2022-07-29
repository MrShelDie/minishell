/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:41:52 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/29 14:48:50 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(
	char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
		f(i++, s);
}
