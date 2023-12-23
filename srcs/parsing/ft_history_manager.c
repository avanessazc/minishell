/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 12:54:19 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/22 20:12:59 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_a_spaces_line(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input);
	while (i < len && ft_strchr(" \t", input[i]) == 1)
		i++;
	if (i == len)
		return (YES);
	return (NO);
}

int	ft_history_manager(t_program *program, char *input)
{
	if (input && *input)
	{
		if (program->old_input == NULL && ft_is_a_spaces_line(input) == NO)
		{
			add_history(input);
			program->old_input = ft_strdup(input);
			if (!program->old_input)
				return (ERR_MALLOC);
		}
		else if (program->old_input != NULL)
		{
			if (ft_strcmp(input, program->old_input) != 0
				&& ft_is_a_spaces_line(input) == NO)
			{
				ft_free_array(&program->old_input);
				add_history(input);
				program->old_input = ft_strdup(input);
				if (!program->old_input)
					return (ERR_MALLOC);
			}
		}
	}
	return (0);
}
