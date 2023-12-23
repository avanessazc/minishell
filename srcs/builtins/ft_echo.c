/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:56:29 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:08:13 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_n_option(char **args, int *i, int *start, int *option_n)
{
	int	j;

	while (args[*i] != NULL)
	{
		if (args[*i] != NULL && ft_strncmp(args[*i], "-n", 2) == 0)
		{
			j = 1;
			while (args[*i][j] != '\0' && ft_strchr("n", args[*i][j]) == YES)
				j++;
			if (args[*i][j] != '\0' && ft_strchr("n", args[*i][j]) == NO)
			{
				*start = 1;
				break ;
			}
			*option_n = 1;
		}
		else
		{
			*start = 1;
			break ;
		}
		*i = *i + 1;
	}	
	return (0);
}

static void	ft_write_args(char **args, int *flag, int i, int len)
{
	(void)len;
	if (ft_strcmp(args[i], " ") == 0)
		*flag = 1;
	if (ft_strcmp(args[i], " ") == 0 && i >= len - 1)
		return ;
	ft_putstr_fd(args[i], STDOUT);
	if (args[i + 1] != NULL && *flag == 0)
	{
		*flag = 1;
		ft_putstr_fd(" ", STDOUT);
	}
}

int	ft_echo(char **args)
{
	int	option_n;
	int	i;
	int	start;
	int	flag;
	int	len;

	option_n = 0;
	i = 1;
	start = 0;
	flag = 0;
	len = 0;
	while (args[len] != NULL)
		len++;
	ft_check_n_option(args, &i, &start, &option_n);
	while (args[i] != NULL && start == 1)
	{
		ft_write_args(args, &flag, i, len);
		flag = 0;
		i++;
	}
	if (option_n == 0)
		ft_putstr_fd("\n", STDOUT);
	return (SUCCESS);
}
