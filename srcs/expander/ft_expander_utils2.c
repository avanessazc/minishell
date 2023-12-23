/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:12:09 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/26 11:16:03 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_equal_symbol(t_program *program)
{
	int		i;
	t_list	*tmp;

	tmp = program->token;
	while (tmp)
	{
		i = 0;
		while (tmp->line[i] != '\0')
		{
			if (tmp->line[i] == '=')
			{
				tmp->check_equal = YES;
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_find_export_cmd(t_program *program)
{
	t_list	*tmp;

	tmp = program->token;
	while (tmp)
	{
		if (ft_strcmp(tmp->line, "export") == 0)
			tmp->check_export = YES;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_find_export_args(t_program *program)
{
	t_list	*tmp;
	int		flag_cmd_export;

	tmp = program->token;
	flag_cmd_export = 0;
	while (tmp)
	{
		if (tmp->check_export == YES)
		{
			flag_cmd_export = 1;
			tmp = tmp->next;
		}
		else
		{
			if (tmp->type == PIPE_TYPE)
				flag_cmd_export = 0;
			else if (flag_cmd_export == 1)
				tmp->check_export = YES;
			tmp = tmp->next;
		}		
	}
	return (0);
}

int	ft_find_cd_cmd(t_program *program)
{
	t_list	*tmp;

	tmp = program->token;
	while (tmp)
	{
		if (ft_strcmp(tmp->line, "cd") == 0)
			tmp->check_cd = YES;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_find_cd_args(t_program *program)
{
	t_list	*tmp;
	int		flag_cmd_cd;

	tmp = program->token;
	flag_cmd_cd = 0;
	while (tmp)
	{
		if (tmp->check_cd == YES)
		{
			flag_cmd_cd = 1;
			tmp = tmp->next;
		}
		else
		{
			if (tmp->type == PIPE_TYPE)
				flag_cmd_cd = 0;
			else if (flag_cmd_cd == 1)
				tmp->check_cd = YES;
			tmp = tmp->next;
		}		
	}
	return (0);
}
