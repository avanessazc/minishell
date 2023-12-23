/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:12:35 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:07:56 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_shlvl(t_program *program, int change)
{
	char	*tab[3];
	char	*shlvl;
	int		ret;
	char	*tmp;

	tab[0] = "export";
	if (ft_get_env(program->env_vars, "SHLVL", &shlvl))
		return (ERR_MALLOC);
	program->shlvl = ft_atoi(shlvl);
	ft_free_array(&shlvl);
	program->shlvl += change;
	tmp = ft_itoa(program->shlvl);
	if (!tmp)
		return (ERR_MALLOC);
	tab[1] = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	if (!tab[1])
		return (ERR_MALLOC);
	tab[2] = NULL;
	ret = ft_export(program, tab, 0, 0);
	if (tab[1])
		free(tab[1]);
	if (ret != 0)
		return (ERR_MALLOC);
	return (0);
}

int	count_args(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

void	print_two_str(char *str1, char *str2, int fd)
{
	ft_putstr_fd(str1, fd);
	ft_putstr_fd(str2, fd);
}

int	print_e(char **args[], char *err, int exit_code, int option)
{
	if (option == 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd((*args)[0], STDERR);
		ft_putstr_fd(err, STDERR);
		ft_putchar_fd('\n', STDERR);
	}
	if (option == 1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd((*args)[0], STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd((*args)[1], STDERR);
		ft_putstr_fd(err, STDERR);
		ft_putchar_fd('\n', STDERR);
	}
	return (exit_code);
}

int	print_e_bis(char **args[], char *err, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(err, STDERR);
	ft_putstr_fd((*args)[1], STDERR);
	ft_putchar_fd('\n', STDERR);
	return (exit_code);
}
