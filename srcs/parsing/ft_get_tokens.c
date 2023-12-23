/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:16:27 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:07:10 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_else(t_get_tokens *gt, t_list **token, t_list *tmp)
{
	if (tmp->line[gt->i] != '\0'
		&& ft_strchr("\"\'", tmp->line[gt->i]) == 1)
	{
		gt->j = gt->i;
		gt->ret = ft_quotes(tmp->line, &gt->i);
		if (gt->ret != 0)
			gt->i = gt->j + 1;
	}
	else if (tmp->line[gt->i] == '\0')
	{
		if (ft_add_new_elem(token, 1) == -1)
			return (ERR_MALLOC);
		if (ft_get_sub_line(token, tmp->line, gt->start, \
		gt->end - gt->start) != 0)
			return (ERR_MALLOC);
		gt->start = -1;
	}
	return (0);
}

static int	ft_get_tokens_util_bis(t_get_tokens *gt, \
t_list **token, t_list *tmp)
{
	while (tmp->line[gt->i] != '\0'
		&& ft_strchr("|<>\"\'", tmp->line[gt->i]) == 0)
		gt->i++;
	gt->end = gt->i;
	if (tmp->line[gt->i] != '\0' && ft_strchr("|", tmp->line[gt->i]) == 1)
	{
		gt->ret = ft_split_by_pipe_and_point_comma_symbol(token, &tmp, \
		&gt->start, &gt->i);
		if (gt->ret != SUCCESS)
			return (gt->ret);
	}
	else if (tmp->line[gt->i] != '\0' && ft_strchr("><", tmp->line[gt->i]) == 1)
	{
		gt->ret = ft_split_by_angle_brackets(token, &tmp, &gt->start, &gt->i);
		if (gt->ret != SUCCESS)
			return (gt->ret);
	}
	else
	{
		if (ft_else(gt, token, tmp) != 0)
			return (ERR_MALLOC);
	}
	return (0);
}

static int	ft_get_tokens_util(t_get_tokens *gt, t_list **token, t_list *tmp)
{
	gt->i = 0;
	gt->start = gt->i;
	while (tmp->line[gt->i] != '\0')
	{
		gt->ret = ft_get_tokens_util_bis(gt, token, tmp);
		if (gt->ret != 0)
			return (gt->ret);
	}
	if (gt->start != -1 && !(gt->start == gt->i))
	{
		if (ft_add_new_elem(token, 1) == -1)
			return (ERR_MALLOC);
		if (ft_get_sub_line(token, tmp->line, gt->start, \
		gt->i - gt->start) != 0)
			return (ERR_MALLOC);
	}	
	return (0);
}

int	ft_get_tokens(t_program *program, int id)
{
	t_get_tokens	gt;
	t_list			*token;
	t_list			*tmp;

	tmp = program->token;
	token = NULL;
	while (tmp)
	{
		gt.ret = ft_get_tokens_util(&gt, &token, tmp);
		if (gt.ret != 0)
		{
			ft_clear_list(&token);
			return (gt.ret);
		}
		tmp = tmp->next;
	}
	tmp = token;
	while (tmp)
	{
		tmp->id = id++;
		tmp = tmp->next;
	}
	ft_clear_list(&program->token);
	program->token = token;
	return (SUCCESS);
}
