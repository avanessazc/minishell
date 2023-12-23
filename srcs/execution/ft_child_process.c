/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 12:22:52 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/05 12:30:52 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_err(char **cmd, char *err)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd[0], STDERR);
	ft_putstr_fd(err, STDERR);
	ft_putchar_fd('\n', STDERR);
}

void	ft_execve(char **path, char **cmd, char **env, t_program *program)
{
	if (execve(cmd[0], cmd, env) == -1)
	{
		if (ft_strncmp(cmd[0], "/", 1) == 0)
		{
			ft_print_err(cmd, ": Is a directory");
			ft_free_tab_split(path);
			ft_free_program(program);
			exit(126);
		}
		if (ft_strncmp(cmd[0], "./", 2) == 0)
		{
			ft_print_err(cmd, ": is not an executable");
			ft_free_tab_split(path);
			ft_free_program(program);
			exit(126);
		}
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(cmd[0], STDERR);
		ft_putstr_fd(": ", STDERR);
		perror("");
		ft_free_program(program);
		ft_free_tab_split(path);
		exit(1);
	}
}

void	ft_execute_command(char *env[], t_program *program, \
char **path, char *path_var)
{
	int		ret;

	check_command(program->clean_args, program);
	ret = ft_get_env(program->env_vars, "PATH", &path_var);
	if (path_var == NULL || ft_strcmp(path_var, "") == 0)
		check_path_linux_cmd(path, program->clean_args, program, &path_var);
	else if (check_path_cmd(path, program->clean_args, program, &path_var) != 0)
	{
		check_if_path_exist(ret, program, &path_var);
		path = ft_split(path_var, ':');
		ft_free_array(&path_var);
		check_split_return(path, program);
		ft_get_cmd(path, &program->clean_args, program, 0);
		check_path_linux_cmd(path, program->clean_args, program, &path_var);
	}
	ft_free_array(&path_var);
	ft_free_before_execute_cmd(program);
	ft_execve(path, program->clean_args, env, program);
	ft_free_tab_split(path);
	ft_free_program(program);
}

void	ft_execute_builtin(t_program *program)
{
	int	ret;

	ft_free_before_execute_builtin(program);
	ret = ft_exec_built_in(program, &program->clean_args);
	if (ret < 0)
	{
		ft_error(program, ret);
		ft_free_program(program);
		exit(1);
	}
	ft_free_program(program);
	exit(ret);
}

void	ft_child_process(char *env[], int process, \
t_program *program, int error)
{
	int	is_builtin;

	pipes_first_cmd(process, program);
	pipes_between_zero_and_last_cmd(process, program);
	pipes_last_cmd(process, program);
	ft_redirect_fdinfile_fdoutfile(program, error);
	if (program->clean_args[0] != NULL)
	{
		is_builtin = ft_is_built_in(program->clean_args[0], program->env_vars);
		if (is_builtin == ERR_MALLOC)
		{
			ft_putstr_fd("Error: malloc failed\n", STDERR);
			ft_free_program(program);
			exit(1);
		}
	}
	if (program->clean_args[0] != NULL && is_builtin == YES)
		ft_execute_builtin(program);
	else if (program->clean_args[0] != NULL)
		ft_execute_command(env, program, NULL, NULL);
	ft_free_program(program);
	exit(0);
}
