/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_one_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:19:24 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:09:09 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect_fdinfile_fdoutfile_one_command(t_program *program, \
int *error)
{
	if (*error == 0)
	{
		if (program->counter_delimiter && program->flag_infile == 1)
		{
			close(program->fd_delimiter[0].fd[WRITE]);
			close(program->fd_delimiter[0].fd[READ]);
		}
		if (program->counter_infile && program->flag_infile == 2)
			close(program->fd_infile);
		if (program->counter_outfile)
		{
			dup2(program->fd_outfile, STDOUT);
			close(program->fd_outfile);
		}
	}
}

int	ft_clean_args(t_program *program, int process)
{
	int	size;
	int	i;
	int	j;

	size = ft_count_new_size(program->to_delete,
			program->args_lst[process].size);
	program->clean_args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!program->clean_args)
		return (ERR_MALLOC);
	i = 0;
	j = 0;
	while (i < program->args_lst[process].size && j < (size + 1))
	{
		if (program->to_delete[i] == ALIVE)
		{
			program->clean_args[j] = ft_strdup(
					program->args_lst[process].args[i]);
			if (!program->clean_args[j])
				return (ERR_MALLOC);
			j++;
		}
		i++;
	}
	program->clean_args[j] = NULL;
	return (0);
}

void	check_clean_args(t_program *program, int i)
{
	if (ft_clean_args(program, i) != 0)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR);
		ft_free_program(program);
		exit(1);
	}
}

int	ft_execution_one_command(t_program *program, int *error)
{
	int	r;

	program->envp = ft_env_to_array(program);
	if (!program->envp)
		return (ERR_MALLOC);
	r = ft_redirections(program, 0, error, 0);
	if (r == ERR_MALLOC)
		return (ERR_MALLOC);
	if (r == CTRL_D_HEREDOC || r == CTRL_C_HEREDOC)
		return (r);
	if (r == 1)
		g_prog->exit_code = 1;
	if (r == 1)
		return (g_prog->exit_code);
	check_clean_args(program, 0);
	ft_free_args_struct(&program->args_lst, program->pipes_nbr + 1);
	ft_redirect_fdinfile_fdoutfile_one_command(program, error);
	r = ft_exec_built_in(program, &program->clean_args);
	if (r == ERR_MALLOC || r == ERR_PIPE || r == ERR_FORK)
		return (r);
	g_prog->exit_code = r;
	dup2(program->std_in, STDIN);
	dup2(program->std_out, STDOUT);
	return (0);
}
