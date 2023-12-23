/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:12:32 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:09:28 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_redir_infile_delimiter(t_program *program, int *j, \
int process, int *error)
{
	int	ret;

	program->delimiter = NULL;
	if (program->args_lst[process].type[*j] == REDIR_LIMITER_TYPE)
	{
		ret = ft_launch_heredoc_check_for_delim(program, j, process);
		if (ret == ERR_MALLOC)
			return (ret);
		if (ret == CTRL_D_HEREDOC)
			return (ret);
		if (ret == CTRL_C_HEREDOC)
			return (ret);
	}
	if (program->args_lst[process].type[*j] == REDIR_INFILE_TYPE)
		if (ft_open_infile_check_fd(program, j, process, error))
			return (1);
	return (0);
}

int	ft_redir_outfile_append(t_program *program, int *j, int process, int *error)
{
	if (program->args_lst[process].args[*j + 1] == NULL)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR);
		*error = 1;
		program->to_delete[*j] = KILL;
		program->counter_outfile++;
		return (0);
	}
	if (program->args_lst[process].type[*j] == REDIR_OUTFILE_TYPE)
		program->fd_outfile = open(program->args_lst[process].args[*j + 1], \
		O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 00664);
	else
		program->fd_outfile = open(program->args_lst[process].args[*j + 1], \
		O_WRONLY | O_CREAT | O_APPEND, 00664);
	if (*error == 0 && check_file_descriptor(program->fd_outfile, \
	program->args_lst[process].args[*j + 1]))
		*error = 1;
	program->to_delete[*j] = KILL;
	program->to_delete[*j + 1] = KILL;
	program->counter_outfile++;
	return (0);
}

static void	ft_redir_util(t_program *program, int process)
{
	program->fd_infile = 0;
	program->fd_outfile = 0;
	program->counter_infile = 0;
	program->counter_outfile = 0;
	program->counter_delimiter = 0;
	program->last_delimiter = 0;
	program->counter_delimiter = ft_count_delimiter(
			program->args_lst[process].args, "<<", &program->last_delimiter, 0);
	if (program->last_delimiter != -1 && program->counter_delimiter > 0)
		program->flag_infile = 1;
	else if (program->last_delimiter == -1)
		program->flag_infile = 2;
	program->to_delete = ft_create_array_int(program->args_lst[process].size,
			ALIVE);
	if (!program->to_delete)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR);
		ft_free_program(program);
		exit(1);
	}
}

int	ft_redirections(t_program *program, int process, int *error, int ret)
{
	int		j;

	j = 0;
	*error = 0;
	ft_redir_util(program, process);
	while (j < program->args_lst[process].size)
	{
		if ((program->args_lst[process].type[j] == REDIR_INFILE_TYPE \
			|| program->args_lst[process].type[j] == REDIR_LIMITER_TYPE)
			&& *error == 0)
			ret = ft_redir_infile_delimiter(program, &j, process, error);
		if (ret)
			return (ret);
		if ((program->args_lst[process].type[j] == REDIR_OUTFILE_TYPE \
			|| program->args_lst[process].type[j] == REDIR_APPEND_TYPE)
			&& *error == 0)
			ft_redir_outfile_append(program, &j, process, error);
		if (program->args_lst[process].args[j] != NULL)
			j = j + 1;
		else
			break ;
	}
	if (*error == 1)
		return (1);
	return (0);
}
