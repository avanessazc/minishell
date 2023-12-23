/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils8.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:07:01 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:07:03 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_avance(t_expanded_var_to_token *evtt)
{
	while (evtt->tmp->line[evtt->i] != '\0'
		&& (evtt->tmp->nq[evtt->i] == QUOTE_DOUBLE_TO_DELETE
			|| evtt->tmp->nq[evtt->i] == QUOTE_SIMPLE_TO_DELETE))
		evtt->i++;
}

void	ft_init_var_evtt(t_expanded_var_to_token *evtt)
{
	evtt->i = 0;
	evtt->start = evtt->i;
	evtt->end = ft_strlen(evtt->tmp->line);
}

int	is_equal(int a, int b)
{
	if ((a == QUOTE_DOUBLE_TO_DELETE || a == QUOTE_SIMPLE_TO_DELETE) && \
		(b == QUOTE_DOUBLE_TO_DELETE || b == QUOTE_SIMPLE_TO_DELETE))
	{
		if (a == b)
			return (YES);
	}
	return (NO);
}
