/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:45:17 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:09:19 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_malloc_delim_pipe_first_heredoc(t_program *program, int process, int j)
{
	signal(SIGQUIT, SIG_IGN);
	ft_free_array_pipe(&program->fd_delimiter);
	program->fd_delimiter = (t_pipe *)malloc(sizeof(t_pipe) * 1);
	if (program->fd_delimiter == NULL)
		return (ERR_MALLOC);
	if (pipe(program->fd_delimiter[0].fd) == -1)
		ft_display_err_free_program("Error: pipe() failed\n", program, 0);
	program->delimiter = ft_strdup(program->args_lst[process].args[j + 1]);
	if (!program->delimiter)
		ft_display_err_free_program("Error: malloc failed\n", program, 0);
	program->input_heredoc = readline("> ");
	if (program->ctrl_c_heredoc == 1 && program->input_heredoc == NULL)
		return (CTRL_D_HEREDOC);
	return (0);
}

void	ft_check_ctrl_c_heredoc_free(t_program *program, int j)
{
	if (program->ctrl_c_heredoc == 0)
		dup2(program->std_in, STDIN);
	ft_free_array_and_fill_to_delete(program, j);
}

int	ft_get_heredoc_lines(t_program *program, int j, int process, char *new_line)
{
	int	ret;

	ret = ft_malloc_delim_pipe_first_heredoc(program, process, j);
	if (ret)
		return (ret);
	while (program->ctrl_c_heredoc == 1 && \
	ft_strcmp(program->input_heredoc, program->delimiter) != 0)
	{
		if (ft_portable_expanser(program, program->input_heredoc, &new_line))
			ft_display_err_free_program("Error: malloc failed\n", program, 1);
		ft_push_expand_hline_to_delim_pipe(program, &new_line);
		program->input_heredoc = readline("> ");
		if (program->ctrl_c_heredoc == 0)
			break ;
		if (program->input_heredoc == NULL)
			return (CTRL_D_HEREDOC);
	}
	ft_check_ctrl_c_heredoc_free(program, j);
	if (program->ctrl_c_heredoc == 0)
		return (CTRL_C_HEREDOC);
	program->to_delete[j] = KILL;
	program->to_delete[j + 1] = KILL;
	return (0);
}

int	ft_loop_intermediary_heredocs(t_program *program, int *j)
{
	while (program->ctrl_c_heredoc == 1 && \
ft_strcmp(program->input_heredoc, program->delimiter) != 0)
	{
		ft_free_array(&program->input_heredoc);
		program->input_heredoc = readline("> ");
		if (program->ctrl_c_heredoc == 0)
			break ;
		if (program->input_heredoc == NULL)
			return (CTRL_D_HEREDOC);
	}
	if (program->ctrl_c_heredoc == 0)
		dup2(program->std_in, STDIN);
	ft_free_array(&program->input_heredoc);
	ft_free_array(&program->delimiter);
	if (program->ctrl_c_heredoc == 0)
		return (CTRL_C_HEREDOC);
	program->to_delete[*j] = KILL;
	program->to_delete[*j + 1] = KILL;
	return (0);
}

int	ft_launch_heredoc_check_for_delim(t_program *program, int *j, int process)
{
	int	ret;

	program->ctrl_c_heredoc = 1;
	if (program->counter_delimiter && program->flag_infile == 1
		&& *j == program->last_delimiter)
	{
		ret = ft_get_heredoc_lines(program, *j, process, NULL);
		if (ret)
			return (ret);
	}
	else
	{
		program->delimiter = ft_strdup(\
		program->args_lst[process].args[*j + 1]);
		if (!program->delimiter)
			return (ERR_MALLOC);
		program->input_heredoc = readline("> ");
		if (program->ctrl_c_heredoc == 1 && program->input_heredoc == NULL)
			return (CTRL_D_HEREDOC);
		ret = ft_loop_intermediary_heredocs(program, j);
		if (ret)
			return (ret);
	}
	return (0);
}
