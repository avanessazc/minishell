/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:07:35 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/26 11:09:26 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_create_array_int(int len, int value)
{
	int	*array;
	int	i;

	array = (int *)malloc(sizeof(int) * len);
	if (!array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		array[i] = value;
		i++;
	}
	return (array);
}

void	ft_classify_quotes(int **quotes, char *line, int i, int t)
{
	int	q;
	int	qtd;

	if (line[t] == '\"')
		q = DOUBLE_QUOTE;
	if (line[t] == '\'')
		q = SINGLE_QUOTE;
	if (line[t] == '\"')
		qtd = QUOTE_DOUBLE_TO_DELETE;
	if (line[t] == '\'')
		qtd = QUOTE_SIMPLE_TO_DELETE;
	(*quotes)[t] = qtd;
	t++;
	while (t < i && line[t] != '\0')
	{
		(*quotes)[t] = q;
		t++;
	}
	(*quotes)[i - 1] = qtd;
}

int	ft_find_quote_zones(int **quotes, char *line, int len)
{
	int	i;
	int	t;
	int	ret;

	i = 0;
	while (i < len && line[i] != '\0')
	{
		while (line[i] != '\0' && ft_strchr("\"\'", line[i]) == 0)
			i++;
		if (line[i] != '\0' && ft_strchr("\"\'", line[i]) == 1)
		{
			t = i;
			ret = ft_quotes(line, &i);
			if (ret != 0)
				i = t + 1;
			else if (ret == 0)
				ft_classify_quotes(quotes, line, i, t);
			continue ;
		}
		i++;
	}
	return (0);
}

int	ft_find_dollar_symbols(int **quotes, char *line, int len)
{
	int	i;

	i = 0;
	while (i < len && line[i] != '\0')
	{
		if (line[i] == '$'
			&& line[i + 1] != '\0' && line[i + 1] != '?')
		{
			if ((*quotes)[i] != SINGLE_QUOTE)
				(*quotes)[i] = DOLLAR_SYMBOL;
		}
		else if (line[i] == '$'
			&& line[i + 1] != '\0' && line[i + 1] == '?')
		{
			if ((*quotes)[i] != SINGLE_QUOTE)
				(*quotes)[i] = DOLLAR_QUESTION_SYMBOLS;
		}
		i++;
	}
	return (0);
}

int	ft_portable_expanser(t_program *program, char *line, char **new_line)
{
	int		*quotes;
	int		len;

	len = ft_strlen(line);
	quotes = ft_create_array_int(len, 0);
	if (!quotes)
		return (ERR_MALLOC);
	ft_find_dollar_symbols(&quotes, line, len);
	*new_line = ft_create_new_line(program, line, quotes, NULL);
	if (!new_line)
		return (ERR_MALLOC);
	if (quotes)
		free(quotes);
	return (0);
}
