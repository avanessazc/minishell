/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:15:57 by abesombe          #+#    #+#             */
/*   Updated: 2021/09/30 17:08:01 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_minus(t_cd *cd, char **args[], t_program *program)
{
	cd->flag_minus = 1;
	if (ft_get_env(program->env_vars, "OLDPWD", &cd->oldpwd) != 0)
		return (ERR_MALLOC);
	if (cd->oldpwd == NULL || ft_strcmp(cd->oldpwd, "") == 0)
		return (print_e(args, ": OLDPWD not set", 1, 0));
	free((*args)[1]);
	(*args)[1] = ft_strdup(cd->oldpwd);
	if ((*args)[1] == NULL)
	{
		ft_free_array(&cd->oldpwd);
		return (ERR_MALLOC);
	}
	return (0);
}

int	ft_cd_empty(char **args[])
{
	ft_free_array(&(*args)[1]);
	(*args)[1] = (char *)malloc(sizeof(char) * 2);
	if (!(*args)[1])
		return (ERR_MALLOC);
	(*args)[1][0] = '.';
	(*args)[1][1] = '\0';
	return (0);
}

int	ft_cd_without_args(t_cd *cd, char **args[], t_program *program)
{
	if (ft_get_env(program->env_vars, "HOME", &cd->home) != 0)
	{
		ft_free_array(&cd->oldpwd);
		return (ERR_MALLOC);
	}
	if (cd->home == NULL)
	{
		ft_free_array(&cd->oldpwd);
		return (print_e(args, ": HOME not set", 1, 0));
	}
	else if (ft_strcmp(cd->home, "") == 0)
	{
		ft_free_array(&cd->home);
		return (2);
	}
	else
	{
		ft_free_array2(*args);
		if (ft_replace_args(cd, args) != 0)
			return (ERR_MALLOC);
	}
	return (0);
}

int	ft_cd_minus_empty_no_args(t_cd *cd, char **args[], t_program *program)
{
	if ((*args)[1] != NULL && ft_strcmp((*args)[1], "-") == 0)
	{
		cd->ret = ft_cd_minus(cd, args, program);
		if (cd->ret != 0)
			return (cd->ret);
	}
	else if ((*args)[1] != NULL && ft_strcmp((*args)[1], "") == 0)
	{
		if (ft_cd_empty(args) != 0)
			return (ERR_MALLOC);
	}
	else if ((*args)[1] == NULL)
	{
		cd->ret = ft_cd_without_args(cd, args, program);
		if (cd->ret != 0)
			return (cd->ret);
	}
	return (0);
}

int	ft_get_cdpath(t_cd *cd, char **args[], t_program *program)
{
	if (ft_get_env(program->env_vars, "CDPATH", &cd->cdpath) != 0)
	{
		ft_free_multi_arrays(&cd->home, &cd->oldpwd, NULL, NULL);
		return (ERR_MALLOC);
	}
	if (cd->cdpath != NULL)
	{
		cd->ext_path_a = ft_strjoin(cd->cdpath, (*args)[1]);
		if (!cd->ext_path_a)
			ft_free_multi_arrays(&cd->home, &cd->oldpwd, &cd->cdpath, NULL);
		if (!cd->ext_path_a)
			return (ERR_MALLOC);
		cd->rep = opendir(cd->ext_path_a);
		if (cd->rep == NULL)
		{
			cd->tmp = ft_strjoin(cd->cdpath, "/");
			cd->ext_path_b = ft_strjoin(cd->tmp, (*args)[1]);
			if (!cd->ext_path_b)
				return (ERR_MALLOC);
			cd->rep = opendir(cd->ext_path_b);
		}
	}
	return (0);
}
