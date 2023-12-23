/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:29:54 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/26 16:33:01 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_array(char **to_free)
{
	if (*to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

void	ft_free_array_int(int **to_free)
{
	if (*to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

void	ft_free_array_pipe(t_pipe **to_free)
{
	if (*to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

void	ft_free_array_processes(pid_t **to_free)
{
	if (*to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

void	ft_free_array2(char **to_free)
{
	int	i;

	i = 0;
	if (to_free)
	{
		while (to_free[i])
		{
			free(to_free[i]);
			to_free[i] = NULL;
			i++;
		}
		free(to_free);
		to_free = NULL;
	}
}
