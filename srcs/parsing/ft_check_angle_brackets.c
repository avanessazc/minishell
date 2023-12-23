/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_angle_brackets.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:08:50 by ayzapata          #+#    #+#             */
/*   Updated: 2021/10/05 18:13:42 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_angle_brackets_util(t_list	*next)
{
	if (next != NULL)
	{
		if (ft_strchr("><", next->line[0]) == 1)
		{
			ft_putstr_fd("syntax error near unexpected token `", STDERR);
			ft_putchar_fd(next->line[0], STDERR);
			ft_putstr_fd("'\n", STDERR);
			g_prog->exit_code = 2;
			return (ERR_PARSER);
		}
	}
	else if (!next)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR);
		g_prog->exit_code = 2;
		return (ERR_PARSER);
	}
	return (0);
}

static int	ft_check_angle_brackets_util_bis(t_list	*next)
{
	if (next != NULL && (next->line[0] == '<' && next->line[1] == '\0'))
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR);
		ft_putchar_fd(next->line[0], STDERR);
		ft_putstr_fd("'\n", STDERR);
		g_prog->exit_code = 2;
		return (ERR_PARSER);
	}
	if (next != NULL && next->line[0] == '<'
		&& (next->line[1] != '\0' && next->line[1] == '<'))
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR);
		ft_putchar_fd(next->line[0], STDERR);
		ft_putchar_fd(next->line[0], STDERR);
		ft_putstr_fd("'\n", STDERR);
		g_prog->exit_code = 2;
		return (ERR_PARSER);
	}
	return (0);
}

/*
** ft_check_angle_brackets:
** This function checkes < > separated or at the end of the line
*/
int	ft_check_angle_brackets(t_program *program, int i)
{
	t_list	*tmp;
	t_list	*next;
	int		l;

	tmp = program->token;
	while (tmp)
	{
		i = 0;
		next = tmp->next;
		l = ft_strlen(tmp->line);
		while (tmp->line[i] != '\0')
			i++;
		if (ft_strchr("><", tmp->line[i - 1]) == 1)
		{
			if (ft_check_angle_brackets_util(next) != 0)
				return (ERR_PARSER);
		}
		else if (l >= 2 && (tmp->line[l - 2] == '>' && tmp->line[l - 1] == '|'))
		{
			if (ft_check_angle_brackets_util_bis(next) != 0)
				return (ERR_PARSER);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
