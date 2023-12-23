/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 19:37:10 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:08:25 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_negative_or_positive(int neg, unsigned long long value)
{
	if (neg == YES)
	{
		if (value > 0 && value <= 255)
			g_prog->exit_code = (int)(value - 256) *-1;
		if (value > 255)
			g_prog->exit_code = 256 - (int)(value % 256);
	}
	if (neg == NO)
	{
		if (value > 0 && value <= 255)
			g_prog->exit_code = (int)value;
		if (value > 255)
			g_prog->exit_code = (int)(value % 256);
	}
}

void	is_negative(char **args, int *neg, int *i)
{
	if (args[1][0] == '-')
	{
		*i = *i + 1;
		*neg = YES;
	}
}

void	get_value(char **args, int neg, unsigned long long *value)
{
	if (neg == NO)
		*value = ft_atoi(args[1]);
	if (neg == YES)
		*value = ft_atoi(&args[1][1]);
}

void	set_exit_code(int neg, unsigned long long value,
												int *exit_cmd, int pipes_nbr)
{
	pipes_nbr_equal_zero(exit_cmd, pipes_nbr, 1);
	if_negative_or_positive(neg, value);
}

void	ft_two_args(char **args, int len, int *exit_cmd, int pipes_nbr)
{
	int					i;
	int					neg;
	int					arg_len;
	unsigned long long	value;

	neg = NO;
	if (len == 2)
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
			get_value(args, neg, &value);
			if (value > MAX_LONG)
				ft_exit_code_two(args, exit_cmd, pipes_nbr);
			else
				set_exit_code(neg, value, exit_cmd, pipes_nbr);
		}
	}
}
