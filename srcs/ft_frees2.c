/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:32:47 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:06:14 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_history(t_program *program)
{
	if (program->old_input != NULL)
		rl_clear_history();
}

int	ft_free_args_struct(t_args **to_free, int len)
{
	int	i;

	if (*to_free)
	{
		i = 0;
		while (i < len)
		{
			ft_free_array2((*to_free)[i].args);
			(*to_free)->args = NULL;
			ft_free_array_int(&(*to_free)[i].type);
			i++;
		}
		free(*to_free);
		*to_free = NULL;
	}
	return (0);
}

int	ft_ie_struct(t_ie **to_free)
{
	if (*to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
	return (0);
}

void	ft_free_multi_arrays(char **str1, char **str2, char **str3, char **str4)
{
	if (str1 != NULL)
		ft_free_array(str1);
	if (str2 != NULL)
		ft_free_array(str2);
	if (str3 != NULL)
		ft_free_array(str3);
	if (str4 != NULL)
		ft_free_array(str4);
}
