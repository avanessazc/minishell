/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:28:06 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/05 11:43:07 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_command(char **cmd, t_program *program)
{
	if (cmd == NULL)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR);
		ft_free_program(program);
		exit(1);
	}
	if (cmd[0] == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(cmd[0], STDERR);
		ft_putstr_fd(": command not found\n", STDERR);
		ft_free_program(program);
		exit(0);
	}
}

void	try_open_path_cmd(char **path, char **cmd, t_program *program, \
char **path_var)
{
	int	fd;

	fd = open(cmd[0], O_RDONLY);
	if (fd < 0)
	{
		print_msg_err_path_cmd(cmd, ": command not found");
		ft_free_path(path, path_var);
		ft_free_program(program);
		exit(127);
	}
	close(fd);
}

int	check_path_cmd(char **path, char **cmd, t_program *program, char **path_var)
{
	struct stat	buf;

	if (ft_strncmp(cmd[0], "./", 2) == 0)
	{
		ft_check_access(path, cmd, program, path_var);
		if (is_directory(cmd[0]))
		{
			print_msg_err_path_cmd(cmd, ": Is a directory");
			ft_free_path(path, path_var);
			ft_free_program(program);
			exit(126);
		}
		if (!(stat(cmd[0], &buf) == 0 && buf.st_mode & S_IXUSR))
		{
			print_msg_err_path_cmd(cmd, ": Permission denied 1");
			ft_free_path(path, path_var);
			ft_free_program(program);
			exit(126);
		}
		try_open_path_cmd(path, cmd, program, path_var);
	}
	else
		return (1);
	return (0);
}

int	check_file_descriptor(int fd, char *file_name)
{
	if (fd == -1)
	{
		if (errno == 13)
		{
			ft_putstr_fd("minishell: ", STDERR);
			ft_putstr_fd(file_name, STDERR);
			ft_putstr_fd(": Permission denied 2", STDERR);
			ft_putchar_fd('\n', STDERR);
		}
		else if (errno == 2)
		{
			ft_putstr_fd("minishell: ", STDERR);
			ft_putstr_fd(file_name, STDERR);
			ft_putstr_fd(": No such file or directory", STDERR);
			ft_putchar_fd('\n', STDERR);
		}
		else
			perror("99");
		return (-1);
	}
	return (0);
}

void	check_if_path_exist(int ret, t_program *program, char **path_var)
{
	if (ret != 0)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR);
		ft_free_program(program);
		ft_free_array(path_var);
		exit(1);
	}
	if ((*path_var) == NULL || ft_strcmp((*path_var), "") == 0)
	{
		ret = access(program->clean_args[0], X_OK);
		if (ret < 0)
		{
			ft_putstr_fd("minishell: ", STDERR);
			ft_putstr_fd(program->clean_args[0], STDERR);
			ft_putstr_fd(": command not found", STDERR);
			ft_putchar_fd('\n', STDERR);
			ft_free_array(path_var);
			ft_free_program(program);
			exit(127);
		}
	}
}
