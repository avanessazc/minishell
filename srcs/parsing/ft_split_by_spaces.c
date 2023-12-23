/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:20:47 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/26 17:01:30 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_splite_by_spaces_util(char *str, int *i)
{
	int	ret;
	int	j;

	ret = 0;
	while (str[*i] != '\0' && ft_strchr("\t ", str[*i]) == 0)
	{
		if (str[*i] != '\0' && ft_strchr("\"\'", str[*i]) == 1)
		{
			j = *i;
			ret = ft_quotes(str, i);
			if (ret != 0)
				*i = j + 1;
		}
		else
			*i = *i + 1;
	}
}

int	ft_split_by_spaces(t_program *program, char *str, int id)
{
	int		i;
	int		start;
	int		end;
	t_list	*tmp;

	i = 0;
	start = i;
	tmp = NULL;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && (str[i] == '\t' || str[i] == ' '))
			i++;
		start = i;
		if (str[i] != '\0')
		{
			ft_splite_by_spaces_util(str, &i);
			end = i;
			if (ft_add_new_elem(&tmp, id++) == -1)
				return (ERR_MALLOC);
			if (ft_get_sub_line(&tmp, str, start, end - start) != 0)
				return (ERR_MALLOC);
		}
	}
	program->token = tmp;
	return (SUCCESS);
}
