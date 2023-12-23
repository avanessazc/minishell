/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:33:28 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:06:21 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int signum)
{
	(void)signum;
	g_prog->exit_code = 130;
	if (g_prog->ctrl_c_heredoc == 1)
	{	
		g_prog->ctrl_c_heredoc = 0;
		close(STDIN);
		ft_putstr_fd("\n", STDERR);
		rl_replace_line("", 0);
		rl_redisplay();
		rl_on_new_line();
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_int_child(int signum)
{
	(void)signum;
	g_prog->exit_code = 130;
	ft_putstr_fd("\n", STDERR);
}

void	signal_ctrl_d_father(t_program *program, char **envp[])
{
	if (program->input == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT);
		ft_free_array(&program->input);
		ft_free_program(program);
		if (program->flag_env_i == 1)
		{
			ft_free_array(&(*envp)[0]);
			free(*envp);
		}
		exit(g_prog->exit_code);
	}
}
