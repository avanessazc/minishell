/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:15:31 by ayzapata          #+#    #+#             */
/*   Updated: 2021/10/05 18:06:30 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl_var(t_program *program, char *str)
{
	char	**var;

	if (ft_get_env(program->env_vars, "SHLVL", &str) != 0)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR);
		ft_free_program(program);
		exit(1);
	}
	if (str == NULL || ft_strcmp(str, "") == 0 || ft_strcmp(str, "0") == 0)
	{
		var = ft_create_double_array("export", "SHLVL=1");
		if (!var)
		{
			ft_free_array(&str);
			ft_free_program(program);
			ft_putstr_fd("Error: malloc failed\n", STDERR);
			exit(1);
		}
		ft_export(program, var, 0, 0);
		ft_free_array(&str);
		ft_free_array2(var);
	}
	else
		ft_free_array(&str);
}
