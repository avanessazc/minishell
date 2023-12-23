/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:03:03 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/05 11:41:34 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab_array_program(char **path, t_program *program, \
char **path_var)
{
	ft_free_tab_split(path);
	ft_free_array(path_var);
	ft_free_program(program);
}

void	ft_check_cmd_dir(char **path, char **cmd, t_program *program, \
char **path_var)
{
	if (ft_strncmp(cmd[0], "./", 2) != 0 && ft_strncmp(cmd[0], "/", 1) != 0)
	{
		print_msg_err_path_cmd(cmd, ": command not found");
		ft_free_tab_array_program(path, program, path_var);
		exit(127);
	}
	else if (ft_strncmp(cmd[0], "./", 2) == 0)
	{
		if (is_directory(cmd[0]))
		{
			print_msg_err_path_cmd(cmd, ": Is a directory");
			ft_free_tab_array_program(path, program, path_var);
			exit(126);
		}
	}
}

void	check_path_linux_cmd(char **path, char **cmd, t_program *program, \
char **path_var)
{
	int	ret;

	ft_check_cmd_dir(path, cmd, program, path_var);
	ret = access(cmd[0], F_OK);
	if (ret == 0)
	{
		ret = access(cmd[0], X_OK);
		if (ret < 0)
		{
			print_msg_err_path_cmd(cmd, ": Permission denied 3");
			ft_free_tab_array_program(path, program, path_var);
			exit(126);
		}
	}
	else if (ret < 0)
	{
		print_msg_err_path_cmd(cmd, ": command not found");
		ft_free_tab_array_program(path, program, path_var);
		exit(127);
	}
}

void	check_split_return(char **path, t_program *program)
{
	if (path == NULL)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR);
		ft_free_program(program);
		ft_free_tab_split(path);
		exit(1);
	}
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}
