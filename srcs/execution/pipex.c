/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 12:22:52 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/02 12:29:24 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_set_exit_code_last_cmd(t_program *program)
{
	int	i;

	i = program->children - 1;
	if (program->launched_children[i] == YES)
	{
		if (program->processes_exit_codes[i] == 130)
			g_prog->exit_code = 130;
		else if (program->processes_exit_codes[i] == 131)
			g_prog->exit_code = 131;
		else
			g_prog->exit_code = WEXITSTATUS(
					program->processes_exit_codes[i]);
	}
}

static int	launch(t_program *program, int *error, int *i)
{
	check_clean_args(program, *i);
	ft_free_array_int(&program->to_delete);
	if (ft_launch_children(program, *i, *error) != 0)
		return (ERR_FORK);
	if (program->counter_delimiter > 0 && program->fd_delimiter != NULL)
	{
		close(program->fd_delimiter[0].fd[READ]);
		close(program->fd_delimiter[0].fd[WRITE]);
	}
	ft_free_array2(program->clean_args);
	program->clean_args = NULL;
	ft_free_array(&program->input_heredoc);
	ft_free_array(&program->delimiter);
	return (0);
}

int	ft_create_children(t_program *program, int *error, int *i)
{
	int	r;

	program->counter_delimiter = 0;
	r = ft_redirections(program, *i, error, 0);
	if (r == ERR_MALLOC)
		return (ERR_MALLOC);
	if (r == CTRL_D_HEREDOC || r == CTRL_C_HEREDOC)
		return (r);
	if (r != 1)
	{
		if (launch(program, error, i) != 0)
			return (ERR_FORK);
	}
	if (r == 1)
	{
		ft_free_array_int(&program->to_delete);
		g_prog->exit_code = 1;
	}
	*i = *i + 1;
	return (0);
}

int	ft_execution_more_than_one_command(t_program *program, int *error)
{
	int	i;
	int	r;

	i = 0;
	r = ft_pipes_mallocs(program, -1);
	if (r != 0)
		return (r);
	program->launched_children = ft_create_array_int(program->children, 0);
	if (program->launched_children == NULL)
		return (ERR_MALLOC);
	i = 0;
	while (i < program->children)
	{
		signal(SIGQUIT, SIG_IGN);
		r = ft_create_children(program, error, &i);
		if (r == ERR_MALLOC)
			return (ERR_MALLOC);
		if (r == CTRL_D_HEREDOC || r == CTRL_C_HEREDOC)
			return (r);
	}
	ft_wait_children(program);
	return (0);
}

int	pipex(t_program *program, int error)
{
	int	ret;
	int	is_builtin;

	program->flag_infile = 0;
	if (ft_tokens_to_array(program) != 0)
		return (ERR_MALLOC);
	ft_clear_list(&program->token);
	ft_ie_struct(&program->limits);
	if (program->args_lst[0].args == NULL)
		return (0);
	is_builtin = ft_is_built_in(program->args_lst[0].args[0], \
	program->env_vars);
	if (is_builtin == ERR_MALLOC)
		return (ERR_MALLOC);
	if (program->pipes_nbr == 0 && (program->args_lst[0].args[0] != NULL
			&& is_builtin == YES))
		return (ft_execution_one_command(program, &error));
	ret = ft_execution_more_than_one_command(program, &error);
	if (ret != 0)
		return (ret);
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, SIG_IGN);
	ft_set_exit_code_last_cmd(program);
	return (g_prog->exit_code);
}
