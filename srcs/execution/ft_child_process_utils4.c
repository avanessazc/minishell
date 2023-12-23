/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process_utils4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:38:18 by ayzapata          #+#    #+#             */
/*   Updated: 2021/10/05 18:20:28 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_path_linux_cmd_copy(char **path, char **cmd, t_program *program, \
char **path_var)
{
	int		ret;
	char    path_pwd_before[PATH_MAX];

	if (getcwd(path_pwd_before, PATH_MAX) == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd("error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory", \
		STDERR);
		ft_putchar_fd('\n', STDERR);
		ft_free_tab_split(path);
		ft_free_array(path_var);
		ft_free_program(program);
		exit(1);
	}
	if (ft_strcmp(cmd[0], ".") == 0 || ft_strcmp(cmd[0], "..") == 0)
	{
		print_msg_err_path_cmd(cmd, ": command not found");
		ft_free_tab_split(path);
		ft_free_array(path_var);
		ft_free_program(program);
		exit(127);
	}
	else if (ft_strncmp(cmd[0], "./", 2) == 0)
	{
		ret = access(cmd[0], F_OK);
		if (ret == 0)
		{
			if (is_directory(cmd[0]))
			{
				print_msg_err_path_cmd(cmd, ": Is a directory");
				ft_free_path(path, path_var);
				ft_free_program(program);
				exit(126);
			}
			ret = access(cmd[0], X_OK);
			if (ret < 0)
			{
				print_msg_err_path_cmd(cmd, ": Permission denied");
				ft_free_tab_split(path);
				ft_free_array(path_var);
				ft_free_program(program);
				exit(126);
			}
		}
		else if (ret < 0)
		{
			print_msg_err_path_cmd(cmd, ": No such file or directory");
			ft_free_tab_split(path);
			ft_free_array(path_var);
			ft_free_program(program);
			exit(127);
		}
	}
	else if (ft_strncmp(cmd[0], "/", 1) == 0)
	{
		ret = access(cmd[0], F_OK);
		if (ret == 0)
		{
			if (is_directory(cmd[0]))
			{
				print_msg_err_path_cmd(cmd, ": Is a directory");
				ft_free_path(path, path_var);
				ft_free_program(program);
				exit(126);
			}
			ret = access(cmd[0], X_OK);
			if (ret < 0)
			{
				print_msg_err_path_cmd(cmd, ": Permission denied");
				ft_free_tab_split(path);
				ft_free_array(path_var);
				ft_free_program(program);
				exit(126);
			}
		}
		else if (ret < 0)
		{
			print_msg_err_path_cmd(cmd, ": No such file or directory");
			ft_free_tab_split(path);
			ft_free_array(path_var);
			ft_free_program(program);
			exit(127);
		}
	}
	else
	{
		
	}
	


}
