/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:24:01 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:08:45 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	case_a(t_program *program, char *str, int j, int found)
{
	t_env	*tmp;
	int		ret;

	tmp = program->env_vars;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, str, j) == 0 && (tmp->str[j] == '='
				|| tmp->str[j] == '\0'))
		{
			ft_free_array(&tmp->str);
			tmp->str = ft_strdup(str);
			if (!tmp->str)
				return (ERR_MALLOC);
			ret = ft_set_env_list_node(&tmp, j);
			if (ret != 0)
				return (ret);
			found = YES;
			break ;
		}
		tmp = tmp->next;
	}
	if (found == NO)
		if (case_a_not_found(program, &tmp, str, j) != 0)
			return (ERR_MALLOC);
	return (0);
}

int	case_b_not_found(t_program *program, t_env **tmp, char *str)
{
	if (ft_add_new_elem_env(&program->env_vars,
			ft_list_size_env(program->env_vars) + 1, str) != 0)
		return (ERR_MALLOC);
	(*tmp) = program->env_vars;
	while (*tmp)
	{
		if (ft_strcmp((*tmp)->str, str) == 0)
		{
			ft_free_array(&(*tmp)->name);
			(*tmp)->name = ft_strdup(str);
			(*tmp)->print = NO;
			if (!(*tmp)->name)
				return (ERR_MALLOC);
			break ;
		}
		(*tmp) = (*tmp)->next;
	}
	return (0);
}

int	case_b(t_program *program, char *str, int j, int found)
{
	t_env	*tmp;

	tmp = program->env_vars;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, str, j) == 0)
		{
			found = YES;
			if ((tmp->str[j] != '\0' && tmp->str[j] == '=')
				|| tmp->str[j] == '\0')
				break ;
			ft_free_array(&tmp->str);
			tmp->str = ft_strdup(str);
			if (!tmp->str)
				return (ERR_MALLOC);
			break ;
		}
		tmp = tmp->next;
	}
	if (found == NO)
		if (case_b_not_found(program, &tmp, str) != 0)
			return (ERR_MALLOC);
	return (0);
}

int	ft_one_or_more_args(t_program *program, char *str, int *error)
{
	int	j;

	if (((str[0] != '\0' && str[0] == '_') && (str[1] != '\0'
				&& str[1] == '='))
		|| ((str[0] != '\0' && str[0] == '_') && str[1] == '\0'))
		return (0);
	j = 0;
	while (str[j] != '\0' && str[j] != '=' && ft_is_env_var_char(str[j]) == YES)
		j++;
	if (case_error(str, j, error) == YES)
		return (0);
	if (str[j] != '\0' && str[j] == '=')
	{
		if (case_a(program, str, j, NO) != 0)
			return (ERR_MALLOC);
	}
	else
	{
		if (case_b(program, str, j, NO) != 0)
			return (ERR_MALLOC);
	}
	return (0);
}

int	ft_export(t_program *program, char **args, int i, int len)
{
	char	*str;
	int		error;

	error = 0;
	while (args[len] != NULL)
		len++;
	if (len == 1)
	{
		if (ft_print_export_list(program->env_vars) != 0)
			return (ERR_MALLOC);
	}
	else
	{
		i = 1;
		while (i < len)
		{
			str = args[i];
			if (ft_one_or_more_args(program, str, &error) != 0)
				return (ERR_MALLOC);
			i++;
		}
	}
	if (error == 1)
		return (1);
	return (SUCCESS);
}
