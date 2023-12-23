/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 13:08:58 by ayzapata          #+#    #+#             */
/*   Updated: 2021/10/05 18:13:51 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	To divide by "|;"
*/
int	ft_split_by_pipe_and_point_comma_symbol(t_list **token, \
t_list **tmp, int *start, int *i)
{
	int	end;

	end = *i;
	if (*start < end)
	{
		if (ft_add_new_elem(token, 1) == -1)
			return (ERR_MALLOC);
		if (ft_get_sub_line(token, (*tmp)->line, *start, end - *start) != 0)
			return (ERR_MALLOC);
	}
	if (ft_add_new_elem(token, 1) == -1)
		return (ERR_MALLOC);
	if (ft_get_sub_line(token, (*tmp)->line, *i, 1) != 0)
		return (ERR_MALLOC);
	*start = end + 1;
	*i = *i + 1;
	return (SUCCESS);
}

/*
**	ft_check_pipe_and_point_comma_symbols:
**	This function checkes:
**	| at the beginning of the line
**	| at the end of the line
*/
int	ft_check_pipe_and_point_comma_symbols(t_program *program)
{
	t_list	*tmp;
	t_list	*next;

	tmp = program->token;
	while (tmp)
	{
		next = tmp->next;
		if ((tmp->line[0] == '|' && next == NULL)
			|| (tmp->line[0] == '|' && tmp->id == 1)
			|| (tmp->line[0] == '|' && next != NULL && next->line[0] == '|'))
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", STDERR);
			g_prog->exit_code = 2;
			return (ERR_PARSER);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

/*
**	ft_check_pipe_point_comma_and_angle_brackets_symbols:
**	This function checkes:
**	>> | at the end of the line
**	< | consecutives
**	> | consecutives
*/
int	ft_check_pipe_point_comma_and_angle_brackets_symbols(t_program *program)
{
	t_list	*tmp;
	t_list	*next;

	tmp = program->token;
	while (tmp)
	{
		next = tmp->next;
		if ((tmp->line[0] == '<' && next != NULL && next->line[0] == '|')
			|| (tmp->line[0] == '>' && next != NULL && next->line[0] == '|')
			|| (tmp->line[0] == '>' && tmp->line[1] == '>'
				&& next != NULL && next->line[0] == '|'))
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", STDERR);
			g_prog->exit_code = 2;
			return (ERR_PARSER);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

void	ft_classify_tokens(t_program *program)
{
	t_list	*tmp;

	tmp = program->token;
	while (tmp)
	{
		if (tmp->line[0] == '|')
			tmp->type = PIPE_TYPE;
		else if (ft_strcmp(tmp->line, "<") == 0)
			tmp->type = REDIR_INFILE_TYPE;
		else if (ft_strcmp(tmp->line, "<<") == 0)
			tmp->type = REDIR_LIMITER_TYPE;
		else if (ft_strcmp(tmp->line, ">") == 0)
			tmp->type = REDIR_OUTFILE_TYPE;
		else if (ft_strcmp(tmp->line, ">>") == 0)
			tmp->type = REDIR_APPEND_TYPE;
		else
			tmp->type = COMMAND_TYPE;
		tmp = tmp->next;
	}
}

int	ft_parser_tokens(t_program *program, char *str, int id)
{
	int	ret;

	ret = ft_split_by_spaces(program, str, id);
	if (ret != SUCCESS)
		return (ret);
	ret = ft_check_angle_brackets(program, 0);
	if (ret != SUCCESS)
		return (ret);
	ret = ft_get_tokens(program, id);
	if (ret != SUCCESS)
		return (ret);
	ret = ft_check_pipe_and_point_comma_symbols(program);
	if (ret != SUCCESS)
		return (ret);
	ret = ft_check_pipe_point_comma_and_angle_brackets_symbols(program);
	if (ret != SUCCESS)
		return (ret);
	ft_classify_tokens(program);
	return (SUCCESS);
}
