/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_title.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:45:00 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/24 12:41:56 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_title(void)
{
	ft_putstr_fd("        _         _        _             _  _\n", STDOUT);
	ft_putstr_fd("       (_)       (_)      | |           | || |\n", STDOUT);
	ft_putstr_fd(" ____   _  ____   _   ___ | | _    ____ | || |\n", STDOUT);
	ft_putstr_fd("|    \\ | ||  _ \\ | | /___)| || \\  / _  )| || |\n", STDOUT);
	ft_putstr_fd("| | | || || | | || ||___ || | | |( (/ / | || |\n", STDOUT);
	ft_putstr_fd("|_|_|_||_||_| |_||_|(___/ |_| |_| \\____)|_||_|\n", STDOUT);
}

void	check_fork(t_program *program, pid_t child)
{
	if (child == -1)
	{
		ft_putstr_fd("Error: fork() failed\n", STDERR);
		ft_free_program(program);
		exit(1);
	}
}

void	ft_start(t_program *program, char *envp[])
{
	pid_t	child;
	int		status;
	char	*cmd[2];
	int		ret;

	cmd[0] = "/usr/bin/clear";
	cmd[1] = NULL;
	status = 0;
	ret = access(cmd[0], X_OK);
	if (ret == -1)
		return ;
	child = fork();
	check_fork(program, child);
	if (child == 0)
	{
		ft_free_array(&program->_var);
		ft_clear_list_env(&program->env_vars);
		ft_execve(NULL, cmd, envp, NULL);
	}
	waitpid(child, &status, 0);
	ft_title();
}
