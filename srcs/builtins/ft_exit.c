/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:18:10 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:06:33 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipes_nbr_equal_zero(int *exit_cmd, int pipes_nbr, int option)
{
	if (pipes_nbr == 0 && option == 1)
	{
		*exit_cmd = 1;
		ft_putstr_fd("exit\n", STDERR);
	}
	if (pipes_nbr == 0 && option == 0)
		ft_putstr_fd("exit\n", STDERR);
}

void	ft_exit_code_two(char **args, int *exit_cmd, int pipes_nbr)
{
	pipes_nbr_equal_zero(exit_cmd, pipes_nbr, 1);
	ft_putstr_fd("exit: ", STDERR);
	ft_putstr_fd(args[1], STDERR);
	ft_putstr_fd(" : numeric argument required\n", STDERR);
	g_prog->exit_code = 2;
}

void	ft_more_then_two_args(char **args, int len,
												int *exit_cmd, int pipes_nbr)
{
	int	i;
	int	neg;
	int	arg_len;

	neg = NO;
	if (len > 2)
	{
		i = 0;
		is_negative(args, &neg, &i);
		arg_len = ft_strlen(args[1]);
		while (args[1][i] != '\0' && ft_isdigit(args[1][i]) == 1)
			i++;
		if ((args[1][i] != '\0' && ft_isdigit(args[1][i]) != 1)
			|| (neg == YES && arg_len == 1))
			ft_exit_code_two(args, exit_cmd, pipes_nbr);
		else
		{
			pipes_nbr_equal_zero(exit_cmd, pipes_nbr, 0);
			ft_putstr_fd("exit: too many arguments\n", STDERR);
			g_prog->exit_code = 1;
		}
	}
}

int	ft_exit(char **args, int *exit_cmd, int pipes_nbr, t_program *program)
{
	int	len;

	(void)program;
	len = 0;
	while (args[len] != NULL)
		len++;
	if (len == 1 && pipes_nbr == 0)
	{
		*exit_cmd = 1;
		ft_putstr_fd("exit\n", STDERR);
		g_prog->exit_code = 0;
	}
	ft_more_then_two_args(args, len, exit_cmd, pipes_nbr);
	ft_two_args(args, len, exit_cmd, pipes_nbr);
	return (g_prog->exit_code);
}
