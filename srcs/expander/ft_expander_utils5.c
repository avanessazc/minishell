/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:25:40 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/26 11:26:26 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_new_token_util(t_list **tempo, t_list *tmp, int len, int start)
{
	int	j;
	int	i;

	j = 0;
	i = start;
	while (j < len)
	{
		(*tempo)->nq[j] = tmp->nq[i];
		i++;
		j++;
	}
	return (0);
}

int	ft_new_token(t_list	**token, t_list	*tmp, int start, int end)
{
	t_list	*tempo;
	int		len;

	if (ft_add_new_elem(token, 1) == -1)
		return (ERR_MALLOC);
	if (ft_get_sub_line(token, tmp->line, start, end - start) != 0)
		return (ERR_MALLOC);
	tempo = *token;
	while (tempo)
	{
		if (!tempo->next)
		{
			len = end - start;
			tempo->type = tmp->type;
			tempo->nq = ft_create_array_int(len, 0);
			if (!tempo->nq)
				return (ERR_MALLOC);
			ft_new_token_util(&tempo, tmp, len, start);
		}
		tempo = tempo->next;
	}
	return (0);
}

int	ft_delete_quote_spaces_a_util(t_list **tmp, char **new_line, int *i, int *j)
{
	if ((*tmp)->nq[*i] != QUOTE_DOUBLE_TO_DELETE
		&& (*tmp)->nq[*i] != QUOTE_SIMPLE_TO_DELETE)
	{
		(*new_line)[*j] = (*tmp)->line[*i];
		*j = *j + 1;
	}
	*i = *i + 1;
	return (0);
}	

int	ft_delete_quote_spaces_a(t_list **tmp, int i, int c, int j)
{
	char	*new_line;

	while ((*tmp)->line[i] != '\0')
	{
		if ((*tmp)->nq[i] != QUOTE_DOUBLE_TO_DELETE
			&& (*tmp)->nq[i] != QUOTE_SIMPLE_TO_DELETE)
			c++;
		i++;
	}
	new_line = (char *)malloc(sizeof(char) * (c + 1));
	if (new_line == NULL)
		return (ERR_MALLOC);
	i = 0;
	while ((*tmp)->line[i] != '\0')
		ft_delete_quote_spaces_a_util(tmp, &new_line, &i, &j);
	new_line[j] = '\0';
	ft_free_array(&(*tmp)->line);
	(*tmp)->line = ft_strdup(new_line);
	ft_free_array(&new_line);
	if (!(*tmp)->line)
		return (ERR_MALLOC);
	return (0);
}

int	ft_delete_quote_spaces(t_program *program, int len, int i, t_list *tmp)
{
	tmp = program->token;
	while (tmp)
	{
		i = 0;
		len = ft_strlen(tmp->line);
		while (tmp->line[i] != '\0' && (tmp->nq[i] == QUOTE_DOUBLE_TO_DELETE
				|| tmp->nq[i] == QUOTE_SIMPLE_TO_DELETE))
			i++;
		if (tmp->line[i] == '\0' && len != 0)
		{
			ft_free_array(&tmp->line);
			tmp->line = ft_strdup(" ");
			if (!tmp->line)
				return (ERR_MALLOC);
		}
		else if (tmp->line[i] != '\0' && (tmp->nq[i] != QUOTE_DOUBLE_TO_DELETE
				&& tmp->nq[i] != QUOTE_SIMPLE_TO_DELETE))
		{
			if (ft_delete_quote_spaces_a(&tmp, i, 0, 0) != 0)
				return (ERR_MALLOC);
		}
		tmp = tmp->next;
	}
	return (0);
}
