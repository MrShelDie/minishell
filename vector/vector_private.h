/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:35:11 by gannemar          #+#    #+#             */
/*   Updated: 2022/07/08 16:11:19 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_PRIVATE_H
# define VECTOR_PRIVATE_H

# define SUCCESS 1
# define FAIL 0

# include "vector.h"
# include <stdbool.h>
# include <sys/types.h>

size_t	data_length(const char *const *data);

char	**copy_data(const char *const *data);

char	**get_value_address(char **data_start, const char *value);

#endif // !VECTOR_PRIVATE_H
