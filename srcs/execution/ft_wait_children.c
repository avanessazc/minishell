/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:50:08 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/02 12:09:03 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipes(t_program *program)
{
	int	j;

	j = 0;
	while (j < program->pipes_nbr && program->pipes_nbr > 0)
	{
		close(program->pipes[j].fd[READ]);
		close(program->pipes[j].fd[WRITE]);
		j++;
	}
}

int	ft_save_processes_exit_codes(t_program *program, int k, int status)
{
	if (WIFSIGNALED(status) == 1)
	{
		if (WTERMSIG(status) == 2)
		{
			if (program->flag_print_nl == 0)
			{
				program->flag_print_nl = 1;
				if (program->ctrl_c_heredoc == 1)
					ft_putstr_fd("\n", STDERR);
			}
			program->processes_exit_codes[k] = 130;
		}
		else if (WTERMSIG(status) == 3)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR);
			program->processes_exit_codes[k] = 131;
		}
	}
	else
		program->processes_exit_codes[k] = status;
	return (0);
}

void	ft_wait_children(t_program *program)
{
	int	k;
	int	status;
	int	i;
	int	ret;

	i = 0;
	while (i < program->children)
	{
		status = 0;
		dup2(program->std_in, STDIN);
		dup2(program->std_out, STDOUT);
		ft_close_pipes(program);
		ret = waitpid(-1, &status, WUNTRACED);
		k = 0;
		while (k < program->children)
		{
			if (program->processes[k] == ret)
			{
				if (ft_save_processes_exit_codes(program, k, status))
					return ;
			}
			k++;
		}
		i++;
	}
}
