/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 12:52:43 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:07:05 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_delete_quotes(t_program *program)
{
	t_list	*tmp;
	char	*new_line;

	tmp = program->token;
	while (tmp)
	{
		new_line = ft_line_after_delete_quotes(tmp->line, tmp->qtdae, &tmp->nq);
		if (!new_line)
			return (ERR_MALLOC);
		ft_free_array(&tmp->line);
		tmp->line = ft_strdup(new_line);
		ft_free_array(&new_line);
		if (!tmp->line)
			return (ERR_MALLOC);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_get_new_line(t_program *program, int len, t_list	**tmp)
{
	int		*quotes;
	char	*new_line;

	new_line = NULL;
	quotes = NULL;
	quotes = ft_create_array_int(len, 0);
	if (!quotes)
		return (ERR_MALLOC);
	ft_find_quote_zones(&quotes, (*tmp)->line, len);
	ft_find_dollar_symbols(&quotes, (*tmp)->line, len);
	new_line = ft_create_new_line(program, (*tmp)->line, quotes,
			&(*tmp)->qtdae);
	ft_free_array_int(&quotes);
	if (!new_line)
		return (ERR_MALLOC);
	ft_free_array(&(*tmp)->line);
	(*tmp)->line = ft_strdup(new_line);
	ft_free_array(&new_line);
	if (!(*tmp)->line)
		return (ERR_MALLOC);
	return (0);
}

int	ft_expander_utils(t_program *program)
{
	if (ft_delete_quotes(program) != 0)
		return (ERR_MALLOC);
	ft_find_equal_symbol(program);
	ft_find_export_cmd(program);
	ft_find_export_args(program);
	ft_find_cd_cmd(program);
	ft_find_cd_args(program);
	if (ft_expanded_var_to_token(program, 1) != 0)
		return (ERR_MALLOC);
	if (ft_split_expanded_var(program, 1) != 0)
		return (ERR_MALLOC);
	if (ft_delete_quote_spaces(program, 0, 0, NULL) != 0)
		return (ERR_MALLOC);
	if (ft_find_pipes_limits(program) != 0)
		return (ERR_MALLOC);
	return (0);
}

int	ft_expander(t_program *program, int len)
{
	t_list	*tmp;
	t_list	*before;

	tmp = program->token;
	before = tmp;
	while (tmp)
	{
		len = ft_strlen(tmp->line);
		if (ft_strcmp(before->line, "<<") != 0)
		{
			if (ft_get_new_line(program, len, &tmp) != 0)
				return (ERR_MALLOC);
		}
		else
		{
			tmp->qtdae = ft_create_array_int(len, 0);
			if (!tmp->qtdae)
				return (ERR_MALLOC);
		}
		before = tmp;
		tmp = tmp->next;
	}
	if (ft_expander_utils(program) != 0)
		return (ERR_MALLOC);
	return (0);
}
