/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:13:40 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/05 17:00:18 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_e_ter(char *arg, char *err, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(err, STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putchar_fd('\n', STDERR);
	return (exit_code);
}

int	ft_replace_args(t_cd *cd, char **args[])
{
	*args = (char **)malloc(sizeof(char *) * 3);
	if (*args == NULL)
		return (ERR_MALLOC);
	(*args)[0] = ft_strdup("cd");
	if ((*args)[0] == NULL)
		return (ERR_MALLOC);
	(*args)[1] = ft_strdup(cd->home);
	if ((*args)[1] == NULL)
		return (ERR_MALLOC);
	(*args)[2] = NULL;
	return (0);
}

int	ft_check_pwd_and_set_oldpwd(t_cd *cd, char **args[], t_program *program)
{
	if (ft_get_env(program->env_vars, "PWD", &cd->pwd))
	{
		ft_free_multi_arrays(NULL, &cd->home, &cd->oldpwd, &cd->cdpath);
		return (ERR_MALLOC);
	}
	if ((*args)[1] != NULL && chdir((*args)[1]) == -1)
	{
		if (cd->flag_path_b == 0)
			ft_free_array(&cd->ext_path_b);
		ft_free_multi_arrays(NULL, &cd->home, &cd->oldpwd, &cd->cdpath);
		return (print_e(args, ": No such file or directory", ERR_CHDIR, 1));
	}
	if (ft_set(program, "OLDPWD", cd->pwd) != 0)
	{
		ft_free_multi_arrays(&cd->home, &cd->pwd, &cd->oldpwd, &cd->cdpath);
		return (ERR_MALLOC);
	}
	ft_free_array(&cd->pwd);
	return (0);
}

void	ft_add_cdpath(t_cd *cd, char **args[])
{
	if (cd->cdpath != NULL && cd->rep != NULL && cd->tmp != NULL)
	{
		cd->flag_path_b = 1;
		ft_free_array(&(*args)[1]);
		(*args)[1] = cd->ext_path_b;
		cd->flag_print_dir = 1;
	}
	else if (cd->cdpath != NULL && cd->rep != NULL)
	{
		ft_free_array(&(*args)[1]);
		(*args)[1] = cd->ext_path_a;
		cd->flag_path_a = 1;
		cd->flag_print_dir = 1;
	}
	else
	{
		cd->rep = opendir((*args)[1]);
	}
	ft_free_multi_arrays(&cd->tmp, NULL, NULL, NULL);
}

void	ft_free_ext_path_a(t_cd *cd)
{
	if (cd->flag_path_a == 0)
		ft_free_array(&cd->ext_path_a);
}
