/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_new_line_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:35:27 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/26 11:38:19 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_code_expander(t_create_new_line *cnl, \
char *exit_code_array, int **qtdae)
{
	int	d;
	int	exit_code_len;

	d = 0;
	exit_code_len = ft_strlen(exit_code_array);
	while (d < exit_code_len)
	{
		cnl->new_line[cnl->j] = exit_code_array[d];
		if (cnl->flag == 1 && qtdae != NULL)
			(*qtdae)[cnl->j] = EXPANSION_EXIT_CODE_BETWEEN_QUOTES;
		else if (qtdae != NULL)
			(*qtdae)[cnl->j] = EXPANSION_EXIT_CODE;
		d++;
		cnl->j++;
	}
	cnl->i = cnl->i + DOLLAR + QUESTION_SYMBOL;
	return (0);
}

int	ft_env_var_expander_util(t_create_new_line *cnl, \
t_env *tmp, int **qtdae)
{
	int	e;

	e = 0;
	while (tmp->value[e] != '\0')
	{
		cnl->new_line[cnl->j] = tmp->value[e];
		if (cnl->flag == 1 && qtdae != NULL)
			(*qtdae)[cnl->j] = EXPANSION_VAR_BETWEEN_QUOTES;
		else if (qtdae != NULL)
			(*qtdae)[cnl->j] = EXPANSION_VAR;
		e++;
		cnl->j++;
	}
	return (0);
}

int	ft_env_var_expander(t_program *program, char *line, \
t_create_new_line *cnl, int **qtdae)
{
	int		t;
	t_env	*tmp;
	int		var_len;

	t = cnl->i;
	cnl->i++;
	while (cnl->i < cnl->len && ft_is_env_var_char(line[cnl->i]) == YES)
		cnl->i++;
	var_len = cnl->i - (t + 1);
	tmp = program ->env_vars;
	while (tmp)
	{
		if (tmp->len_name > var_len)
			cnl->length = tmp->len_name;
		else
			cnl->length = var_len;
		if (ft_strncmp(&line[t + 1], tmp->name, cnl->length) == 0
			&& tmp->equals_symbol == YES)
		{
			ft_env_var_expander_util(cnl, tmp, qtdae);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_init_var(t_create_new_line *cnl, char *line, \
t_program *program, int *quotes)
{
	cnl->flag = 0;
	cnl->i = 0;
	cnl->j = 0;
	cnl->len = ft_strlen(line);
	cnl->new_line_len = ft_new_line_length(program, line, quotes, cnl->len);
	if (cnl->new_line_len == ERR_MALLOC)
		return (ERR_MALLOC);
	return (0);
}	

int	ft_init_var_bis(t_create_new_line *cnl, int **qtdae)
{
	if (qtdae != NULL)
	{
		*qtdae = ft_create_array_int(cnl->new_line_len, 0);
		if (!(*qtdae))
			return (ERR_MALLOC);
	}
	cnl->new_line = (char *)malloc(sizeof(char) * (cnl->new_line_len + 1));
	if (!cnl->new_line)
		return (ERR_MALLOC);
	return (0);
}
