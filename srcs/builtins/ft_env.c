/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:39:17 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/05 12:09:25 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_msg_error_env(char **args)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(args[0], STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(args[1], STDERR);
	ft_putstr_fd(": No such file or directory", STDERR);
	ft_putchar_fd('\n', STDERR);
}

int	ft_env(t_env *env, t_program *program, char **args)
{
	t_env	*tmp;

	if (args[1])
	{
		ft_msg_error_env(args);
		return (127);
	}
	tmp = env;
	while (tmp)
	{
		if (tmp->print == YES)
		{
			ft_putstr_fd(tmp->str, STDOUT);
			ft_putstr_fd("\n", STDOUT);
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("_=", STDOUT);
	ft_putstr_fd(program->_var, STDOUT);
	ft_putstr_fd("/./minishell\n", STDOUT);
	return (SUCCESS);
}
