/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_new_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:59:09 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/26 11:36:43 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_new_line_util(t_create_new_line *cnl, \
char *line, int *quotes, int **qtdae)
{
	cnl->flag = 1;
	if (cnl->i + 1 < cnl->len && (quotes[cnl->i] == quotes[cnl->i + 1]))
	{
		(*qtdae)[cnl->j] = quotes[cnl->i];
		(*qtdae)[cnl->j + 1] = quotes[cnl->i + 1];
		cnl->new_line[cnl->j] = line[cnl->i];
		cnl->new_line[cnl->j + 1] = line[cnl->i + 1];
		cnl->j = cnl->j + 2;
		cnl->i = cnl->i + 2;
		cnl->flag = 0;
	}
	else
	{
		(*qtdae)[cnl->j] = quotes[cnl->i];
		cnl->new_line[cnl->j++] = line[cnl->i++];
	}
}

void	ft_create_new_line_util_bis(t_create_new_line *cnl, \
char *line, int *quotes, int **qtdae)
{
	(*qtdae)[cnl->j] = quotes[cnl->i];
	cnl->new_line[cnl->j++] = line[cnl->i++];
	cnl->flag = 0;
}

void	ft_create_new_line_util_ter(t_create_new_line *cnl, \
char *line, int **qtdae)
{
	if (cnl->flag == 1)
		(*qtdae)[cnl->j] = BETWEEN_QUOTES;
	cnl->new_line[cnl->j++] = line[cnl->i++];
}

char	*ft_create_new_line(t_program *program, \
char *line, int *quotes, int **qtdae)
{
	t_create_new_line	cnl;

	if (ft_init_var(&cnl, line, program, quotes) == ERR_MALLOC)
		return (NULL);
	if (ft_init_var_bis(&cnl, qtdae) == ERR_MALLOC)
		return (NULL);
	while (cnl.i < cnl.len && cnl.j < cnl.new_line_len)
	{
		if (quotes[cnl.i] == DOLLAR_QUESTION_SYMBOLS)
			ft_exit_code_expander(&cnl, program->exit_code_array, qtdae);
		else if (quotes[cnl.i] == DOLLAR_SYMBOL
			&& line[cnl.i + 1] != '\0' && line[cnl.i + 1] != '$')
			ft_env_var_expander(program, line, &cnl, qtdae);
		else if ((quotes[cnl.i] == QUOTE_DOUBLE_TO_DELETE
				|| quotes[cnl.i] == QUOTE_SIMPLE_TO_DELETE) && cnl.flag == 0)
			ft_create_new_line_util(&cnl, line, quotes, qtdae);
		else if ((quotes[cnl.i] == QUOTE_DOUBLE_TO_DELETE
				|| quotes[cnl.i] == QUOTE_SIMPLE_TO_DELETE) && cnl.flag == 1)
			ft_create_new_line_util_bis(&cnl, line, quotes, qtdae);
		else
			ft_create_new_line_util_ter(&cnl, line, qtdae);
	}
	cnl.new_line[cnl.j] = '\0';
	return (cnl.new_line);
}
