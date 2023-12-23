/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:20:57 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:08:40 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	case_error(char *str, int j, int *error)
{
	if ((str[0] != '\0' && (ft_isalpha(str[0]) == NO && str[0] != '_'))
		|| (str[j] != '\0' && ft_is_env_var_char(str[j]) == NO
			&& str[j] != '='))
	{
		ft_putstr_fd("export: `", STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putstr_fd("': not a valid identifier\n", STDERR);
		*error = 1;
		return (YES);
	}
	return (NO);
}

int	case_a_not_found(t_program *program, t_env **tmp, char *str, int j)
{
	int	ret;

	if (ft_add_new_elem_env(&program->env_vars,
			ft_list_size_env(program->env_vars) + 1, str) != 0)
		return (ERR_MALLOC);
	*tmp = program->env_vars;
	while (*tmp)
	{
		if ((*tmp)->next == NULL)
		{
			ret = ft_set_env_list_node(&(*tmp), j);
			if (ret != 0)
				return (ret);
		}
		(*tmp) = (*tmp)->next;
	}
	return (0);
}
