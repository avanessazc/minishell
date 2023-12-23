/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:21:01 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/26 11:34:14 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_id(int id, t_list **token)
{
	t_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		tmp->id = id++;
		tmp = tmp->next;
	}
}

static int	ft_split_expanded_var_util(t_list **token, \
t_list *tmp, int *i, t_se *se)
{
	*i = 0;
	while (tmp->line[*i] != '\0')
	{
		while (tmp->line[*i] != '\0'
			&& ft_strchr(" \t", tmp->line[*i]) == YES)
			*i = *i + 1;
		se->start = *i;
		while (tmp->line[*i] != '\0' && ft_strchr(" \t", tmp->line[*i]) == NO)
			*i = *i + 1;
		se->end = *i;
		if (se->start < se->end)
		{
			if (ft_new_token(token, tmp, se->start, se->end) != 0)
				return (ERR_MALLOC);
		}
		*i = se->end;
	}
	return (0);
}

int	ft_split_expanded_var(t_program *program, int id)
{
	int		i;
	t_list	*token;
	t_se	se;
	t_list	*tmp;

	token = NULL;
	tmp = program->token;
	while (tmp)
	{
		if (tmp->line && tmp->line[0] != '\0' && tmp->nq[0] == EXPANSION_VAR)
		{
			if (ft_split_expanded_var_util(&token, tmp, &i, &se) != 0)
				return (ERR_MALLOC);
		}
		else
		{
			if (ft_new_token(&token, tmp, 0, ft_strlen(tmp->line)) != 0)
				return (ERR_MALLOC);
		}
		tmp = tmp->next;
	}
	ft_set_id(id, &token);
	ft_clear_list(&program->token);
	program->token = token;
	return (0);
}
