/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process_utils3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:38:18 by ayzapata          #+#    #+#             */
/*   Updated: 2021/10/05 11:31:06 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_msg_err_path_cmd(char **cmd, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd[0], STDERR);
	ft_putstr_fd(msg, STDERR);
	ft_putchar_fd('\n', STDERR);
}

void	ft_check_access(char **path, char **cmd, t_program *program, \
char **path_var)
{
	if (access(cmd[0], F_OK) != 0)
	{
		ft_msg_error_env(cmd);
		ft_free_path(path, path_var);
		ft_free_program(program);
		exit(126);
	}
}
