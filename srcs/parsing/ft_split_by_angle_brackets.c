/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_angle_brackets.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:12:05 by ayzapata          #+#    #+#             */
/*   Updated: 2021/10/05 18:13:57 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	case_a(t_list **tmp, int *i)
{
	if ((*tmp)->line[*i] == '>' && ((*tmp)->line[*i + 1] != '\0'
			&& ft_strchr("<", (*tmp)->line[*i + 1]) == 1))
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR);
		ft_putchar_fd((*tmp)->line[*i + 1], STDERR);
		ft_putstr_fd("'\n", STDERR);
		g_prog->exit_code = 2;
		return (ERR_PARSER);
	}
	return (0);
}

static int	case_b(t_list **tmp, int count, int j)
{
	if (count > 1)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR);
		ft_putchar_fd((*tmp)->line[j - 1], STDERR);
		if (count > 2)
			ft_putchar_fd((*tmp)->line[j - 1], STDERR);
		if (count >= 5 && (*tmp)->line[j - 1] == '<')
			ft_putchar_fd((*tmp)->line[j - 1], STDERR);
		ft_putstr_fd("'\n", STDERR);
		g_prog->exit_code = 2;
		return (ERR_PARSER);
	}
	return (0);
}

static int	case_c(t_list **token, t_list **tmp, int *start, int end)
{
	if (*start < end)
	{
		if (ft_add_new_elem(token, 1) == -1)
			return (ERR_MALLOC);
		if (ft_get_sub_line(token, (*tmp)->line, *start, end - *start) != 0)
			return (ERR_MALLOC);
	}
	return (0);
}

/*
**	To split by '>' or '<'
*/
int	ft_split_by_angle_brackets(t_list **token, \
t_list **tmp, int *start, int *i)
{
	int	count;
	int	j;
	int	end;

	end = *i;
	if (case_a(tmp, i) != 0)
		return (ERR_PARSER);
	j = *i + 1;
	while ((*tmp)->line[j] != '\0'
		&& ft_strchr("><", (*tmp)->line[j]) == 1)
		j++;
	count = j - (*i + 1);
	if (case_b(tmp, count, j) != 0)
		return (ERR_PARSER);
	if (case_c(token, tmp, start, end) != 0)
		return (ERR_MALLOC);
	if (ft_add_new_elem(token, 1) == -1)
		return (ERR_MALLOC);
	if (ft_get_sub_line(token, (*tmp)->line, *i, count + 1) != 0)
		return (ERR_MALLOC);
	*start = end + 1 + count;
	*i = *i + 1 + count;
	return (SUCCESS);
}
