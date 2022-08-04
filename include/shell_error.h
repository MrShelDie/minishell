/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:06:03 by gannemar          #+#    #+#             */
/*   Updated: 2022/08/04 19:13:10 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ERROR_H
# define SHELL_ERROR_H

# define PROGRAM_NAME "minishell"

void	print_error(const char *msg);
void	print_error_ambiguous_redirect(const char *pattern);
void	print_error_with_file(const char *file_name, const char *msg);

void	exit_with_error_msg(const char *msg, int exit_status);

#endif
