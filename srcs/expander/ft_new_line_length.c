/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_line_length.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:54:16 by ayzapata          #+#    #+#             */
/*   Updated: 2021/10/05 10:23:57 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_env_var_char(int c)
{
	int	answer;

	answer = NO;
	if (ft_isdigit(c) == YES || ft_isalpha(c) == YES || c == '_')
		answer = YES;
	return (answer);
}

void	ft_init_ntl(int *i, int len, char *line, t_next_text_len *ntl)
{
	ntl->t = *i;
	*i = *i + 1;
	while (*i < len && ft_is_env_var_char(line[*i]) == YES)
		*i = *i + 1;
	ntl->var_len = *i - (ntl->t + 1);
	ntl->found = NO;
}

static int	ft_new_text_len(t_program *program, int *i, int len, char *line)
{
	t_next_text_len	ntl;

	ft_init_ntl(i, len, line, &ntl);
	ntl.tmp = program->env_vars;
	ntl.new_text_len = 0;
	while (ntl.tmp)
	{
		if (ntl.tmp->len_name > ntl.var_len)
			ntl.len = ntl.tmp->len_name;
		else
			ntl.len = ntl.var_len;
		if (ft_strncmp(&line[ntl.t + 1], ntl.tmp->name, ntl.len) == 0
			&& ntl.tmp->equals_symbol == YES)
		{
			ntl.new_text_len = ntl.new_text_len - ntl.var_len - DOLLAR
				+ ntl.tmp->len_value;
			ntl.found = YES;
			break ;
		}
		ntl.tmp = ntl.tmp->next;
	}
	if (ntl.found == NO)
		ntl.new_text_len = ntl.new_text_len - ntl.var_len - DOLLAR;
	return (ntl.new_text_len);
}

int	ft_exit_code_to_array(t_program *program)
{
	ft_free_array(&program->exit_code_array);
	program->exit_code_array = ft_itoa(g_prog->exit_code);
	if (!program->exit_code_array)
		return (ERR_MALLOC);
	program->exit_code_len = ft_strlen(program->exit_code_array);
	return (0);
}

int	ft_new_line_length(t_program *program, char *line, int *quotes, int len)
{
	int	i;
	int	new_line_len;

	i = 0;
	new_line_len = len;
	while (i < len)
	{
		if (quotes[i] == DOLLAR_QUESTION_SYMBOLS)
		{
			new_line_len = new_line_len - DOLLAR - QUESTION_SYMBOL
				+ program->exit_code_len;
			i++;
		}
		else if (quotes[i] == DOLLAR_SYMBOL
			&& line[i + 1] != '\0' && line[i + 1] != '$')
			new_line_len = new_line_len
				+ ft_new_text_len(program, &i, len, line);
		else
			i++;
	}
	return (new_line_len);
}
