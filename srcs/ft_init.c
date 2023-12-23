/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 12:38:41 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:06:18 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_cd(t_cd *cd)
{
	cd->rep = NULL;
	cd->oldpwd = NULL;
	cd->cdpath = NULL;
	cd->pwd = NULL;
	cd->tmp = NULL;
	cd->ext_path_a = NULL;
	cd->ext_path_b = NULL;
	cd->cur_dir = NULL;
	cd->home = NULL;
	cd->flag_minus = 0;
	cd->flag_print_dir = 0;
	cd->flag_path_a = 0;
	cd->flag_path_b = 0;
	cd->err_msg = ": error retrieving current directory: \
getcwd: cannot access parent directories: No such file or \
directory";
}

void	ft_init_program(t_program *program)
{
	program->flag_env_i = 0;
	program->exit_code = 0;
	program->std_in = dup(STDIN);
	program->std_out = dup(STDOUT);
	program->exit = 0;
	program->env_vars = NULL;
	program->old_input = NULL;
	program->_var = NULL;
	program->exit_code_array = NULL;
	ft_re_init_program(program);
}

void	ft_re_init_program(t_program *program)
{
	program->flag_print_nl = 0;
	program->fd_delimiter = NULL;
	program->token = NULL;
	program->envp = NULL;
	program->pipes_nbr = 0;
	program->args_lst = NULL;
	program->limits = NULL;
	program->pipes = NULL;
	program->children = 0;
	program->to_delete = NULL;
	program->processes = NULL;
	program->launched_children = NULL;
	program->processes_exit_codes = NULL;
	program->clean_args = NULL;
	program->input_heredoc = NULL;
	program->input = NULL;
	program->delimiter = NULL;
	program->ctrl_c_heredoc = 0;
}
