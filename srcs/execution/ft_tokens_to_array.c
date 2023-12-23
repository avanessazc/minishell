/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:22:00 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:09:32 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokens_to_array_util(t_program *program, int *i, t_list **tmp, int j)
{
	program->args_lst[*i].size = (program->limits[*i].end \
	- program->limits[*i].init);
	program->args_lst[*i].args = (char **)malloc(sizeof(char *) * \
	 (program->args_lst[*i].size + 1));
	if (!program->args_lst[*i].args)
		return (ERR_MALLOC);
	program->args_lst[*i].type = (int *)malloc(sizeof(int) * \
	(program->args_lst[*i].size));
	if (!program->args_lst[*i].type)
		return (ERR_MALLOC);
	j = 0;
	while ((*tmp) && j < program->args_lst[*i].size)
	{
		program->args_lst[*i].args[j] = ft_strdup((*tmp)->line);
		if (!program->args_lst[*i].args[j])
			return (ERR_MALLOC);
		program->args_lst[*i].type[j] = (*tmp)->type;
		j++;
		(*tmp) = (*tmp)->next;
	}
	if ((*tmp) && (*tmp)->type == PIPE_TYPE)
		(*tmp) = (*tmp)->next;
	program->args_lst[*i].args[j] = NULL;
	*i = *i + 1;
	return (0);
}

int	ft_tokens_to_array(t_program *program)
{
	t_list	*tmp;
	int		i;

	program->args_lst = (t_args *)malloc(sizeof(t_args)
			* (program->pipes_nbr + 1));
	if (!program->args_lst)
		return (ERR_MALLOC);
	i = 0;
	while (i < (program->pipes_nbr + 1))
	{
		program->args_lst[i].args = NULL;
		program->args_lst[i].type = NULL;
		i++;
	}
	tmp = program->token;
	i = 0;
	while (tmp && i < (program->pipes_nbr + 1))
	{
		if (ft_tokens_to_array_util(program, &i, &tmp, 0) != 0)
			return (ERR_MALLOC);
	}
	return (0);
}
