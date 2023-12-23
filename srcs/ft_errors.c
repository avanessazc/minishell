/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:12:44 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:06:11 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(t_program *program, int err)
{
	char	 *msg_error;

	(void)program;
	msg_error = NULL;
	if (ERR_QUOTE == 2)
		msg_error = "Error: syntax error quote\n";
	else if (err == ERR_MALLOC)
		msg_error = "Error: Malloc failed\n";
	else if (err == ERR_ENV_VAR)
		msg_error = "Error: Environment variable\n";
	else if (err == ERR_GET_CWD)
		msg_error = "Error: Path result too large\n";
	else if (err == ERR_PIPE)
		msg_error = "Error: pipe() failed\n";
	else if (err == ERR_FORK)
		msg_error = "Error: fork() failed\n";
	else if (err == ERR_CHDIR)
		msg_error = "Error: No such file or directory\n";
	else if (err == ERR_OPENDIR)
		msg_error = "Error: No such file or directory\n";
	else if (err == ERR_CLOSEDIR)
		msg_error = "Error: No such file or directory\n";
	write(STDERR, msg_error, ft_strlen(msg_error));
	return (1);
}

void	check_main_args(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", STDERR);
		exit(0);
	}
}
