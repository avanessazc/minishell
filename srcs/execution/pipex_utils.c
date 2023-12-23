/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:28:15 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/05 15:55:09 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_env(t_env *env, char *var, char **value)
{
	t_env	*tmp;
	int		len;

	len = ft_strlen(var);
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0 && tmp->print == YES)
		{
			*value = ft_strdup(&tmp->str[len + EQUAL_SYMBOL]);
			if (!(*value))
				return (ERR_MALLOC);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	check_str(char *str, char **path, t_program *program)
{
	if (str == NULL)
	{
		ft_free_tab_split(path);
		ft_free_program(program);
		ft_putstr_fd("Error: malloc failed\n", STDERR);
		exit(0);
	}	
}

void	ft_get_cmd(char **path, char **cmd[], t_program *program, int i)
{
	char	*str;
	char	*tmp;
	int		fd;

	if ((ft_strcmp((*cmd)[0], ".") == 0 || ft_strcmp((*cmd)[0], "..") == 0) || \
	((*cmd)[0] && ((*cmd)[0][0] != '\0' && (*cmd)[0][0] == '/')))
		return ;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		check_str(tmp, path, program);
		str = ft_strjoin(tmp, (*cmd)[0]);
		ft_free_array(&tmp);
		check_str(str, path, program);
		fd = open(str, O_RDONLY);
		if (fd >= 0)
		{
			close(fd);
			ft_free_array(&(*cmd)[0]);
			(*cmd)[0] = str;
			break ;
		}
		i++;
		ft_free_array(&str);
	}
}

int	ft_is_built_in(char	*str, t_env *env)
{
	(void)env;
	if (!str)
		return (NO);
	if (ft_strcmp(str, "echo") == 0)
		return (YES);
	if (ft_strcmp(str, "cd") == 0)
		return (YES);
	if (ft_strcmp(str, "pwd") == 0)
		return (YES);
	if (ft_strcmp(str, "export") == 0)
		return (YES);
	if (ft_strcmp(str, "unset") == 0)
		return (YES);
	if (ft_strcmp(str, "env") == 0)
		return (YES);
	if (ft_strcmp(str, "exit") == 0)
		return (YES);
	return (NO);
}

int	ft_exec_built_in(t_program *program, char **args[])
{
	int		ret;

	ret = 0;
	if (ft_strcmp((*args)[0], "echo") == 0)
		ret = ft_echo(*args);
	if (ft_strcmp((*args)[0], "cd") == 0)
		ret = ft_cd(program, &(*args));
	if (ft_strcmp((*args)[0], "pwd") == 0)
		ret = ft_pwd(program);
	if (ft_strcmp((*args)[0], "export") == 0)
		ret = ft_export(program, (*args), 0, 0);
	if (ft_strcmp((*args)[0], "unset") == 0)
		ret = ft_unset(program, (*args));
	if (ft_strcmp((*args)[0], "env") == 0)
		ret = ft_env(program->env_vars, program, (*args));
	if (ft_strcmp((*args)[0], "exit") == 0)
		ret = ft_exit((*args), &program->exit, program->pipes_nbr, program);
	return (ret);
}
