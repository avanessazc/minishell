/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:47:12 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:09:16 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_err_free_program(char *err, t_program *program, int option)
{
	ft_putstr_fd(err, STDERR);
	ft_free_program(program);
	if (option)
	{
		close(program->fd_delimiter[0].fd[READ]);
		close(program->fd_delimiter[0].fd[WRITE]);
	}
	exit(1);
}

void	ft_push_expand_hline_to_delim_pipe(t_program *program, char **new_line)
{
	ft_putstr_fd(*new_line, program->fd_delimiter[0].fd[WRITE]);
	ft_putstr_fd("\n", program->fd_delimiter[0].fd[WRITE]);
	ft_free_array(&program->input_heredoc);
	ft_free_array(new_line);
}

void	ft_free_array_and_fill_to_delete(t_program *program, int j)
{
	ft_free_array(&program->delimiter);
	program->to_delete[j] = KILL;
	program->to_delete[j + 1] = KILL;
}
