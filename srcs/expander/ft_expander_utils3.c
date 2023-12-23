/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:17:58 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:06:45 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_init_laq(t_line_after_quotes	*laq, char *line, \
int *qtdae, int **nq)
{
	laq->i = 0;
	laq->j = 0;
	laq->flag = 0;
	laq->len = ft_strlen(line);
	laq->new_line_len = laq->len;
	laq->new_line_len = laq->new_line_len
		- ft_count_quotes_to_delete(qtdae, laq->new_line_len);
	*nq = ft_create_array_int(laq->new_line_len, 0);
	if (!(*nq))
		return (ERR_MALLOC);
	laq->new_line = (char *)malloc(sizeof(char) * (laq->new_line_len + 1));
	if (!laq->new_line)
		return (ERR_MALLOC);
	return (0);
}

void	ft_create_nq_content(t_line_after_quotes *laq, \
int *qtdae, int **nq, int copy_i)
{
	int	count;

	count = 0;
	while (laq->i + 1 < laq->len && \
is_equal(qtdae[laq->i], qtdae[laq->i + 1]) == YES)
	{
		count++;
		laq->i = laq->i + 2;
		laq->flag = 0;
	}
	if (laq->i < laq->len && copy_i - 1 >= 0)
		laq->i = copy_i + (count * 2);
	else
	{
		laq->k = 0;
		laq->i = copy_i;
		while (laq->k < count)
		{
			(*nq)[laq->j] = qtdae[laq->i];
			laq->new_line[laq->j] = ' ';
			laq->k++;
			laq->i = laq->i + 2;
			laq->j++;
		}
	}	
}

static void	ft_line_after_delete_quotes_util(t_line_after_quotes *laq, \
int *qtdae, int **nq)
{
	int	copy_i;

	laq->flag = 1;
	copy_i = laq->i;
	if (laq->i + 1 < laq->len && \
is_equal(qtdae[laq->i], qtdae[laq->i + 1]) == YES)
		ft_create_nq_content(laq, qtdae, nq, copy_i);
	else
		laq->i++;
}

char	*ft_line_after_delete_quotes(char *line, int *qtdae, int **nq)
{
	t_line_after_quotes	laq;

	if (ft_init_laq(&laq, line, qtdae, nq) != 0)
		return (NULL);
	while (laq.i < laq.len && laq.j < laq.new_line_len)
	{
		if ((qtdae[laq.i] == QUOTE_DOUBLE_TO_DELETE
				|| qtdae[laq.i] == QUOTE_SIMPLE_TO_DELETE) && laq.flag == 0)
		{
			ft_line_after_delete_quotes_util(&laq, qtdae, nq);
		}
		else if ((qtdae[laq.i] == QUOTE_DOUBLE_TO_DELETE
				|| qtdae[laq.i] == QUOTE_SIMPLE_TO_DELETE) && laq.flag == 1)
		{
			laq.flag = 0;
			laq.i++;
		}
		else
		{
			(*nq)[laq.j] = qtdae[laq.i];
			laq.new_line[laq.j++] = line[laq.i++];
		}
	}
	laq.new_line[laq.j] = '\0';
	return (laq.new_line);
}
