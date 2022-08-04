/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medric <medric@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:06:03 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 15:34:07 by medric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ERROR_H
# define SHELL_ERROR_H

# define PROGRAM_NAME "minishell"

void	print_error(const char *msg);

void	exit_with_error_msg(const char *msg, int exit_status);

#endif
