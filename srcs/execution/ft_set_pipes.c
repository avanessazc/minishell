/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:21:59 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/02 12:28:07 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_pipes(t_list *token)
{
	t_list	*tmp;
	int		pipes;

	tmp = token;
	pipes = 0;
	while (tmp)
	{
		if (tmp->type == PIPE_TYPE)
			pipes++;
		tmp = tmp->next;
	}
	return (pipes);
}

int	ft_pipes_mallocs(t_program *program, int j)
{
	int	i;

	program->children = program->pipes_nbr + 1;
	if (program->pipes_nbr > 0)
	{
		program->pipes = (t_pipe *)malloc(sizeof(t_pipe) * program->pipes_nbr);
		if (program->pipes == NULL)
			return (ERR_MALLOC);
	}
	i = 0;
	while (i < program->pipes_nbr && program->pipes_nbr > 0)
	{
		if (pipe(program->pipes[i].fd) == -1)
			return (ERR_PIPE);
		i++;
	}
	program->processes = (pid_t *)malloc(sizeof(pid_t) * program->children);
	if (program->processes == NULL)
		return (ERR_MALLOC);
	while (++j < program->children)
		program->processes[j] = 0;
	program->processes_exit_codes = ft_create_array_int(program->children, 0);
	if (program->processes_exit_codes == NULL)
		return (ERR_MALLOC);
	return (0);
}

void	pipes_first_cmd(int process, t_program *program)
{
	int	i;

	if (process == 0 && program->pipes_nbr > 0)
	{
		i = 1;
		while (i < program->pipes_nbr)
		{
			close(program->pipes[i].fd[WRITE]);
			close(program->pipes[i].fd[READ]);
			i++;
		}
		close(program->pipes[0].fd[READ]);
		dup2(program->pipes[0].fd[WRITE], STDOUT);
		close(program->pipes[0].fd[WRITE]);
	}
}

void	pipes_between_zero_and_last_cmd(int process, t_program *program)
{
	int	i;

	if (process > 0 && process < program->children - 1
		&& program->pipes_nbr > 0)
	{
		i = 1;
		while (i < program->pipes_nbr)
		{
			close(program->pipes[i - 1].fd[WRITE]);
			close(program->pipes[i].fd[READ]);
			if (program->counter_infile == 0 && program->counter_delimiter == 0)
				dup2(program->pipes[i - 1].fd[READ], STDIN);
			close(program->pipes[i - 1].fd[READ]);
			dup2(program->pipes[i].fd[WRITE], STDOUT);
			close(program->pipes[i].fd[WRITE]);
			i++;
		}
	}
}

void	pipes_last_cmd(int process, t_program *program)
{
	int	i;

	if (process == program->children - 1 && program->pipes_nbr > 0)
	{
		i = 0;
		while (i < program->pipes_nbr - 1)
		{
			close(program->pipes[i].fd[WRITE]);
			close(program->pipes[i].fd[READ]);
			i++;
		}
		close(program->pipes[program->pipes_nbr - 1].fd[WRITE]);
		dup2(program->pipes[program->pipes_nbr - 1].fd[READ], STDIN);
		close(program->pipes[program->pipes_nbr - 1].fd[READ]);
	}
}
