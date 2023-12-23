/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 09:30:19 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/02 13:28:04 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_program *program)
{
	char	*value;
	char	path[PATH_MAX];

	value = NULL;
	if (ft_get_env(program->env_vars, "PWD", &value) != 0)
		return (ERR_MALLOC);
	if (value == NULL)
	{
		if (getcwd(path, PATH_MAX) == NULL)
		{
			ft_putstr_fd("pwd", STDERR);
			ft_putstr_fd(": ", STDERR);
			ft_putstr_fd("error retrieving current directory: getcwd: \
				cannot access parent directories: No such file or directory", \
			STDERR);
			ft_putchar_fd('\n', STDERR);
			return (1);
		}
		ft_putstr_fd(path, STDOUT);
	}
	ft_putstr_fd(value, STDOUT);
	ft_putstr_fd("\n", STDOUT);
	ft_free_array(&value);
	return (SUCCESS);
}
