/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:06:03 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/02 14:26:55 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define PROGRAM_NAME "minishell"

void	print_error(const char *msg);

void	exit_with_error_msg(const char *msg, int exit_status);

#endif
