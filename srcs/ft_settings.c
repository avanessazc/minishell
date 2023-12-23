/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:15:31 by ayzapata          #+#    #+#             */
/*   Updated: 2021/10/05 17:43:24 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_oldpwd(t_program *program)
{
	char	*args[3];

	args[0] = "unset";
	args[1] = "OLDPWD";
	args[2] = NULL;
	ft_unset(program, args);
}

char	**ft_create_double_array(char *s1, char *s2)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * 3);
	if (tab == NULL)
		return (NULL);
	tab[0] = ft_strdup(s1);
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}
	tab[1] = ft_strdup(s2);
	if (!tab[1])
	{
		free(tab[0]);
		free(tab);
		return (NULL);
	}
	tab[2] = NULL;
	return (tab);
}

int	set_terminal(t_program *program)
{
	char	**var;
	char	path[PATH_MAX];
	char	*tmp;

	var = ft_create_double_array("export", "SHLVL=1");
	if (!var)
		return (ERR_MALLOC);
	ft_export(program, var, 0, 0);
	ft_free_array2(var);
	if (getcwd(path, PATH_MAX) == NULL)
		return (ERR_GET_CWD);
	tmp = ft_strjoin("PWD=", path);
	if (!tmp)
		return (ERR_MALLOC);
	var = ft_create_double_array("export", tmp);
	ft_free_array(&tmp);
	if (!var)
		return (ERR_MALLOC);
	ft_export(program, var, 0, 0);
	ft_free_array2(var);
	return (0);
}

int	set_env_var(t_program *program, char **envp[], int ret)
{
	if (!(*envp) || !(**envp))
	{
		program->flag_env_i = 1;
		(*envp) = (char **)malloc(sizeof(char *) * 3);
		if (!(*envp))
			return (ERR_MALLOC);
		(*envp)[0] = ft_strdup("TERM=xterm-256color");
		if (!(*envp)[0])
			return (ERR_MALLOC);
		(*envp)[1] = NULL;
	}
	ret = ft_env_var_to_list(&program->env_vars, *envp);
	if (ret != 0)
	{
		ft_free_program(program);
		ft_error(program, ret);
		exit(1);
	}
	if (program->flag_env_i == 1)
	{
		ret = set_terminal(program);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

void	set__var(t_program *program)
{
	if (ft_get_env(program->env_vars, "PWD", &program->_var) != 0)
	{
		ft_free_program(program);
		ft_error(program, ERR_MALLOC);
		exit(1);
	}
}
