/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_children.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:53:44 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/02 12:18:34 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_minishell_cmd(t_program *program)
{
	if (ft_strcmp(program->clean_args[0], "./minishell") == 0)
	{
		if (ft_update_shlvl(program, 1) == ERR_MALLOC)
		{
			ft_putstr_fd("Error: malloc failed\n", STDERR);
			ft_free_program(program);
			exit(1);
		}
	}
}

void	ft_set_envp(t_program *program)
{
	program->envp = ft_env_to_array(program);
	if (!program->envp)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR);
		ft_free_program(program);
		exit(1);
	}
}

int	ft_launch_children(t_program *program, int i, int error)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	program->launched_children[i] = YES;
	if (program->clean_args[0] == NULL || \
	ft_strcmp(program->clean_args[0], "") == 0)
		return (0);
	signal(SIGINT, &sig_int_child);
	program->processes[i] = fork();
	if (program->processes[i] == -1)
		return (ERR_FORK);
	else if (program->processes[i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		check_minishell_cmd(program);
		ft_free_args_struct(&program->args_lst, program->pipes_nbr + 1);
		ft_set_envp(program);
		ft_free_array_processes(&program->processes);
		ft_free_array_int(&program->processes_exit_codes);
		ft_free_history(program);
		ft_free_array(&program->old_input);
		ft_child_process(program->envp, i, program, error);
	}
	return (0);
}
