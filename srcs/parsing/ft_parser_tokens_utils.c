/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_tokens_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:24:32 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/26 16:24:54 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quotes(char *str, char c, int *i)
{
	*i = *i + 1;
	while (str[*i] != '\0')
	{
		if (str[*i] == c)
			break ;
		*i = *i + 1;
	}
	if (str[*i] == '\0')
		return (ERR_QUOTE);
	*i = *i + 1;
	return (0);
}

int	ft_quotes(char *str, int *i)
{
	int	ret;

	if (str[*i] != '\0' && str[*i] == '\'')
	{
		ret = ft_check_quotes(str, '\'', i);
		if (ret != 0)
			return (ret);
	}
	else if (str[*i] != '\0' && str[*i] == '\"')
	{
		ret = ft_check_quotes(str, '\"', i);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

int	ft_get_sub_line(t_list **list, char *str, int start, int len)
{
	t_list	*tmp;

	tmp = *list;
	if (tmp->next == NULL)
	{
		tmp->line = ft_substr(str, start, len);
		if (tmp->line == NULL)
			return (ERR_MALLOC);
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			tmp->line = ft_substr(str, start, len);
			if (tmp->line == NULL)
				return (ERR_MALLOC);
		}
		tmp = tmp->next;
	}
	return (0);
}
