/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:54:37 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:09:25 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_delimiter(char **str, char *delimiter, int *last_delimiter, \
int count)
{
	int	i;
	int	j;

	*last_delimiter = 0;
	i = -1;
	count = 0;
	while (str[++i] != NULL)
		if (ft_strcmp(str[i], delimiter) == 0)
			count++;
	j = i - 1;
	while (j >= 0)
	{
		if (ft_strcmp(str[j], "<") == 0 && *last_delimiter == 0)
		{
			*last_delimiter = -1;
			break ;
		}
		else if (ft_strcmp(str[j], delimiter) == 0 && *last_delimiter != -1)
		{
			*last_delimiter = j;
			break ;
		}
		j--;
	}
	return (count);
}

int	ft_open_infile_check_fd(t_program *program, int *j, int process, int *error)
{
	if (program->args_lst[process].args[*j + 1] == NULL)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR);
		*error = 1;
		program->to_delete[*j] = KILL;
		program->counter_infile++;
		return (0);
	}
	program->fd_infile = open(program->args_lst[process].args[*j + 1],
			O_RDONLY);
	if (*error == 0 && check_file_descriptor(program->fd_infile, \
	program->args_lst[process].args[*j + 1]) == -1)
		*error = 1;
	program->to_delete[*j] = KILL;
	program->to_delete[*j + 1] = KILL;
	program->counter_infile++;
	return (0);
}

void	ft_redirect_fdinfile_fdoutfile(t_program *program, int error)
{
	if (error == 0)
	{
		if (program->counter_delimiter && program->flag_infile == 1 && \
		program->fd_delimiter != NULL)
		{
			close(program->fd_delimiter[0].fd[WRITE]);
			dup2(program->fd_delimiter[0].fd[READ], STDIN);
			close(program->fd_delimiter[0].fd[READ]);
		}
		if (program->counter_infile && program->flag_infile == 2)
		{
			dup2(program->fd_infile, STDIN);
			close(program->fd_infile);
		}
		if (program->counter_outfile)
		{
			dup2(program->fd_outfile, STDOUT);
			close(program->fd_outfile);
		}
	}	
}

int	ft_count_new_size(int *array, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (array[i] == ALIVE)
			count++;
		i++;
	}
	return (count);
}
