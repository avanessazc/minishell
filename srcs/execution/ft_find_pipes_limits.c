/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_pipes_limits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:26:18 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:09:12 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_find_pipes_limits_util(t_program *program, int *flag, \
int *i, t_list *tmp)
{
	if (*flag == 1)
	{
		program->limits[*i].init = tmp->id;
		*flag = 0;
	}
	if (tmp->type == PIPE_TYPE || tmp->next == NULL)
	{
		if (tmp->next == NULL)
			program->limits[*i].end = tmp->id + 1;
		else
			program->limits[*i].end = tmp->id;
		*i = *i + 1;
		*flag = 1;
	}
}

int	ft_find_pipes_limits(t_program *program)
{
	t_list	*tmp;
	int		i;
	int		flag;

	flag = 1;
	program->limits = (t_ie *)malloc(sizeof(t_ie) * (program->pipes_nbr + 1));
	if (!program->limits)
		return (ERR_MALLOC);
	tmp = program->token;
	i = 0;
	while (tmp && i < (program->pipes_nbr + 1))
	{
		ft_find_pipes_limits_util(program, &flag, &i, tmp);
		tmp = tmp->next;
	}
	return (0);
}
