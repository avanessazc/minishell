/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 11:40:14 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:08:58 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_unset_var_first_position(t_env **tmp, t_env **env)
{
	t_env	*next;

	next = (*tmp)->next;
	if ((*tmp)->str)
		free((*tmp)->str);
	if ((*tmp)->name)
		free((*tmp)->name);
	if ((*tmp)->value)
		free((*tmp)->value);
	free((*tmp));
	*env = next;
	(*tmp) = *env;
	while ((*tmp))
	{
		(*tmp)->id = (*tmp)->id - 1;
		(*tmp) = (*tmp)->next;
	}
	return (SUCCESS);
}

static int	ft_unset_var_other_position(t_env **tmp, t_env **before)
{
	t_env	*next;

	next = (*tmp)->next;
	if ((*tmp)->str)
		free((*tmp)->str);
	if ((*tmp)->name)
		free((*tmp)->name);
	if ((*tmp)->value)
		free((*tmp)->value);
	free((*tmp));
	(*before)->next = next;
	(*tmp) = (*before);
	(*tmp) = (*tmp)->next;
	while ((*tmp))
	{
		(*tmp)->id = (*tmp)->id - 1;
		(*tmp) = (*tmp)->next;
	}
	return (SUCCESS);
}

int	ft_unset_variable(t_env **env, char *unset)
{
	t_env	*tmp;
	t_env	*before;
	int		len;

	len = ft_strlen(unset);
	tmp = *env;
	while (tmp)
	{
		if (tmp->equals_symbol == YES && len == tmp->len_name
			&& ft_strcmp(unset, tmp->name) == 0)
		{
			if (tmp->id == 1)
				return (ft_unset_var_first_position(&tmp, env));
			else
				return (ft_unset_var_other_position(&tmp, &before));
		}
		before = tmp;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	ft_check_env_var_characters(char *unset, int *error)
{
	int	j;

	j = 0;
	while (unset[j] != '\0' && ft_is_env_var_char(unset[j]) == YES)
		j++;
	if ((unset[0] != '\0' && (ft_isalpha(unset[0]) == NO && unset[0] != '_'))
		|| (unset[j] != '\0' && ft_is_env_var_char(unset[j]) == NO))
	{
		ft_putstr_fd("unset: `", STDERR);
		ft_putstr_fd(unset, STDERR);
		ft_putstr_fd("': not a valid identifier\n", STDERR);
		*error = 1;
		return (1);
	}
	return (SUCCESS);
}

int	ft_unset(t_program *program, char **args)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (args[i] != NULL)
	{
		if (ft_check_env_var_characters(args[i], &error) == SUCCESS)
			ft_unset_variable(&program->env_vars, args[i]);
		i++;
	}
	if (error == 1)
		return (1);
	return (SUCCESS);
}
