/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils7.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:31:26 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:06:47 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expanded_var_to_token_util(t_expanded_var_to_token *evtt)
{
	t_list	*tempo;

	if (ft_add_new_elem(&evtt->token, 1) == -1)
		return (ERR_MALLOC);
	tempo = evtt->token;
	while (tempo)
	{
		if (!tempo->next)
		{
			tempo->line = ft_strdup("");
			if (!tempo->line)
				return (ERR_MALLOC);
			evtt->len = 1;
			tempo->type = evtt->tmp->type;
			tempo->nq = ft_create_array_int(evtt->len, 0);
			if (!tempo->nq)
				return (ERR_MALLOC);
		}
		tempo = tempo->next;
	}
	evtt->tmp = evtt->tmp->next;
	return (0);
}

int	ft_case_one(t_expanded_var_to_token *evtt)
{
	while (evtt->tmp->line[evtt->i] != '\0' && evtt->tmp->line[evtt->i] != ' ')
		evtt->i++;
	evtt->end = evtt->i;
	if (evtt->start < evtt->end)
	{
		if (ft_new_token(&evtt->token, evtt->tmp, evtt->start, evtt->end) != 0)
			return (ERR_MALLOC);
	}
	evtt->i = evtt->end;
	while (evtt->tmp->line[evtt->i] != '\0' && evtt->tmp->line[evtt->i] == ' ')
		evtt->i++;
	evtt->start = evtt->i;
	while (evtt->tmp->line[evtt->i] != '\0'
		&& evtt->tmp->nq[evtt->i] == EXPANSION_VAR)
		evtt->i++;
	evtt->end = evtt->i;
	if ((evtt->tmp->line[evtt->i] != '\0'
			&& evtt->tmp->nq[evtt->i] != EXPANSION_VAR)
		|| (evtt->tmp->line[evtt->i] == '\0' && evtt->end - evtt->start > 0))
	{
		if (ft_new_token(&evtt->token, evtt->tmp, evtt->start, evtt->end) != 0)
			return (ERR_MALLOC);
	}	
	return (0);
}

int	ft_expanded_var_to_token_util_bis(t_expanded_var_to_token *evtt)
{
	evtt->i = 0;
	while (evtt->tmp->line[evtt->i] != '\0')
	{
		evtt->start = evtt->i;
		while (evtt->tmp->line[evtt->i] != '\0'
			&& evtt->tmp->nq[evtt->i] != EXPANSION_VAR)
			evtt->i++;
		evtt->end = evtt->i;
		if (evtt->tmp->line[evtt->i] != '\0'
			&& evtt->tmp->nq[evtt->i] == EXPANSION_VAR)
		{
			if (ft_case_one(evtt) != 0)
				return (ERR_MALLOC);
		}
		else if (evtt->tmp->line[evtt->i] == '\0' && evtt->start < evtt->end)
		{
			if (ft_new_token(&evtt->token, evtt->tmp,
					evtt->start, evtt->end) != 0)
				return (ERR_MALLOC);
		}
		evtt->i = evtt->end;
	}
	return (0);
}

int	ft_expanded_var_to_token_util_ter(t_expanded_var_to_token *evtt)
{
	if (evtt->tmp->type == REDIR_INFILE_TYPE
		|| evtt->tmp->type == REDIR_LIMITER_TYPE
		|| evtt->tmp->type == REDIR_OUTFILE_TYPE
		|| evtt->tmp->type == REDIR_APPEND_TYPE
		|| evtt->tmp->type == PIPE_TYPE || evtt->tmp->check_export == YES)
	{
		if (ft_new_token(&evtt->token, evtt->tmp, evtt->start, evtt->end) != 0)
			return (ERR_MALLOC);
	}
	else
	{
		if (ft_expanded_var_to_token_util_bis(evtt) != 0)
			return (ERR_MALLOC);
	}
	return (0);
}

int	ft_expanded_var_to_token(t_program *program, int id)
{
	t_expanded_var_to_token	evtt;

	evtt.token = NULL;
	evtt.tmp = program->token;
	while (evtt.tmp)
	{
		ft_init_var_evtt(&evtt);
		if (evtt.tmp->check_cd == YES)
		{
			ft_avance(&evtt);
			if (evtt.tmp->line[evtt.i] == '\0')
			{
				if (ft_expanded_var_to_token_util(&evtt) != 0)
					return (ERR_MALLOC);
				continue ;
			}
		}
		if (ft_expanded_var_to_token_util_ter(&evtt) != 0)
			return (ERR_MALLOC);
		evtt.tmp = evtt.tmp->next;
	}
	ft_set_id(id, &evtt.token);
	ft_clear_list(&program->token);
	program->token = evtt.token;
	return (0);
}
