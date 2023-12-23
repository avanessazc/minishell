/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 16:21:36 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/05 10:59:36 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cdpath_errors(t_cd *cd, char **args[])
{
	char	path[PATH_MAX];

	if (cd->rep != NULL)
	{
		if (getcwd(path, PATH_MAX) == NULL)
		{
			ft_free_ext_path_a(cd);
			ft_free_multi_arrays(NULL, &cd->home, &cd->oldpwd, &cd->cdpath);
			return (print_e(args, cd->err_msg, 0, 0));
		}
	}
	if (cd->rep == NULL && ft_strcmp((*args)[1], "..") == 0)
	{
		ft_free_ext_path_a(cd);
		ft_free_multi_arrays(NULL, &cd->home, &cd->oldpwd, &cd->cdpath);
		return (print_e(args, cd->err_msg, 1, 0));
	}
	if (cd->rep == NULL)
	{
		if (cd->flag_path_a == 0)
			ft_free_array(&cd->ext_path_a);
		ft_free_multi_arrays(NULL, &cd->home, &cd->oldpwd, &cd->cdpath);
		return (print_e(args, ": No such file or directory", 1, 1));
	}
	return (2);
}

int	ft_set_pwd_util(t_cd *cd, char **args[], t_program *program)
{
	if (ft_set(program, "PWD", cd->cur_dir) != 0)
	{
		ft_free_multi_arrays(&cd->cur_dir, &cd->home, &cd->oldpwd, \
		&cd->cdpath);
		if (cd->rep != NULL && closedir(cd->rep) == -1)
			return (print_e_bis(args, ": No such file or directory", 1));
		return (ERR_MALLOC);
	}
	ft_free_array(&cd->cur_dir);
	if (cd->rep != NULL && closedir(cd->rep) == -1)
	{
		if (cd->flag_path_b == 0)
			ft_free_array(&cd->ext_path_b);
		ft_free_multi_arrays(NULL, &cd->home, &cd->oldpwd, &cd->cdpath);
		return (print_e_bis(args, ": No such file or directory", 1));
	}
	if ((*args)[1] != NULL && cd->flag_minus)
		print_two_str(cd->oldpwd, "\n", STDOUT);
	return (0);
}

int	ft_set_pwd(t_cd *cd, char **args[], t_program *program)
{
	int	ret;

	cd->cur_dir = getcwd(cd->cur_dir, PATH_MAX);
	if (!cd->cur_dir)
	{
		if (cd->flag_path_b == 0)
			ft_free_array(&cd->ext_path_b);
		ft_free_multi_arrays(&cd->cur_dir, &cd->home, &cd->oldpwd, &cd->cdpath);
		if (cd->rep != NULL && closedir(cd->rep) == -1)
			return (print_e_bis(args, ": No such file or directory", 1));
		return (print_e_ter(cd->cur_dir, ": No such file or directory", 1));
	}
	if (cd->flag_print_dir && cd->flag_minus == 0)
		print_two_str(cd->cur_dir, "\n", STDOUT);
	ret = ft_set_pwd_util(cd, args, program);
	if (ret != 0)
	{
		if (cd->flag_path_b == 0)
			ft_free_array(&cd->ext_path_b);
		return (ret);
	}
	if (cd->flag_path_b == 0)
		ft_free_array(&cd->ext_path_b);
	ft_free_multi_arrays(&cd->cur_dir, &cd->home, &cd->oldpwd, &cd->cdpath);
	return (0);
}

int	ft_check_empty_rep_and_close(t_cd *cd, char **args[])
{
	if (cd->flag_path_b == 0)
		ft_free_array(&cd->ext_path_b);
	if (cd->rep != NULL && closedir(cd->rep) == -1)
	{
		ft_free_multi_arrays(NULL, &cd->home, &cd->oldpwd, &cd->cdpath);
		return (print_e_bis(args, ": No such file or directory", 1));
	}
	return (cd->ret);
}

int	ft_cd(t_program *program, char **args[])
{
	t_cd	cd;

	ft_init_cd(&cd);
	cd.ret = ft_cd_minus_empty_no_args(&cd, args, program);
	if (cd.ret == 2)
		return (0);
	if (cd.ret != 0)
		return (cd.ret);
	if (ft_strcmp((*args)[1], ".") != 0 && ft_strcmp((*args)[1], "..") != 0)
		if (ft_get_cdpath(&cd, args, program) == ERR_MALLOC)
			return (ERR_MALLOC);
	ft_add_cdpath(&cd, args);
	cd.ret = ft_cdpath_errors(&cd, args);
	if (cd.ret != 2)
	{
		if (cd.flag_path_a == 0)
			ft_free_array(&cd.ext_path_a);
		return (ft_check_empty_rep_and_close(&cd, args));
	}
	if (cd.flag_path_a == 0)
		ft_free_array(&cd.ext_path_a);
	cd.ret = ft_check_pwd_and_set_oldpwd(&cd, args, program);
	if (cd.ret != 0)
		return (ft_check_empty_rep_and_close(&cd, args));
	return (ft_set_pwd(&cd, args, program));
}
