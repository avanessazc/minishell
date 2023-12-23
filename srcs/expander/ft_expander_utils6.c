/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils6.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:25:42 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:06:46 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_increment_if_sister_quotes(int *i, int *flag, int *count)
{
	(*count)++;
	*i = *i + 2;
	*flag = 0;
}

void	ft_increment_c(int *c, int *flag)
{
	*c = *c + 1;
	*flag = 0;
}

void	ft_init_counters(int *c, int *count, int *copy_i, int *i)
{
	*c = 0;
	*copy_i = *i;
	*count = 0;
}

int	ft_count_quotes_to_delete_util(int *quotes, int len, int *i, int *flag)
{
	int	c;
	int	copy_i;
	int	count;

	ft_init_counters(&c, &count, &copy_i, i);
	if ((quotes[*i] == QUOTE_DOUBLE_TO_DELETE
			|| quotes[*i] == QUOTE_SIMPLE_TO_DELETE) && *flag == 0)
	{
		*flag = 1;
		if (*i + 1 < len && is_equal(quotes[*i], quotes[*i + 1]) == YES)
		{
			while (*i + 1 < len && is_equal(quotes[*i], quotes[*i + 1]) == YES)
				ft_increment_if_sister_quotes(i, flag, &count);
			if (*i < len && copy_i - 1 >= 0)
				c = c + (count * 2);
			else
				c = c + count;
		}
		else
			c++;
	}
	else if ((quotes[*i] == QUOTE_DOUBLE_TO_DELETE
			|| quotes[*i] == QUOTE_SIMPLE_TO_DELETE) && *flag == 1)
		ft_increment_c(&c, flag);
	return (c);
}

int	ft_count_quotes_to_delete(int *quotes, int len)
{
	int	i;
	int	c;
	int	flag;

	i = 0;
	c = 0;
	flag = 0;
	while (i < len)
	{
		c = c + ft_count_quotes_to_delete_util(quotes, len, &i, &flag);
		i++;
	}
	return (c);
}
