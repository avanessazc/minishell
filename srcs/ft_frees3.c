/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:34:33 by ayzapata          #+#    #+#             */
/*   Updated: 2021/10/01 19:52:48 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_ctro_d_heredoc(t_program *program)
{
	ft_clear_list(&program->token);
	ft_free_array2(program->envp);
	program->envp = NULL;
	ft_free_args_struct(&program->args_lst, program->pipes_nbr + 1);
	ft_ie_struct(&program->limits);
	ft_free_array_pipe(&program->pipes);
	ft_free_array_processes(&program->processes);
	ft_free_array_int(&program->processes_exit_codes);
	ft_free_array_int(&program->to_delete);
	ft_clear_list_env(&program->env_vars);
	ft_free_history(program);
	ft_free_array(&program->old_input);
	ft_free_array(&program->_var);
	ft_free_array(&program->input);
	ft_free_array(&program->delimiter);
	ft_free_array(&program->input_heredoc);
}

void	ft_free_before_execute_cmd(t_program *program)
{
	ft_clear_list(&program->token);
	ft_free_args_struct(&program->args_lst, program->pipes_nbr + 1);
	ft_ie_struct(&program->limits);
	ft_free_array_pipe(&program->pipes);
	ft_free_array_processes(&program->processes);
	ft_free_array_int(&program->processes_exit_codes);
	ft_free_array_int(&program->to_delete);
	ft_free_array(&program->input_heredoc);
	ft_clear_list_env(&program->env_vars);
	ft_free_history(program);
	ft_free_array(&program->old_input);
	ft_free_array(&program->_var);
	ft_free_array(&program->exit_code_array);
	ft_free_array(&program->input);
	ft_free_array(&program->delimiter);
}

void	ft_free_before_execute_builtin(t_program *program)
{
	ft_free_array_int(&program->to_delete);
	ft_free_array(&program->exit_code_array);
	ft_free_array(&program->delimiter);
}

void	ft_free_all(t_program *program)
{
	ft_clear_list(&program->token);
	ft_free_array2(program->envp);
	program->envp = NULL;
	ft_free_args_struct(&program->args_lst, program->pipes_nbr + 1);
	ft_ie_struct(&program->limits);
	ft_free_array_pipe(&program->pipes);
	ft_free_array_pipe(&program->fd_delimiter);
	ft_free_array_processes(&program->processes);
	ft_free_array_int(&program->processes_exit_codes);
	ft_free_array_int(&program->to_delete);
	ft_free_array_int(&program->launched_children);
	ft_free_array2(program->clean_args);
	program->clean_args = NULL;
	ft_free_array(&program->input_heredoc);
	ft_free_array(&program->exit_code_array);
	ft_free_array(&program->delimiter);
	ft_free_array(&program->input);
}

void	ft_free_program(t_program *program)
{
	ft_free_history(program);
	ft_free_array(&program->old_input);
	ft_clear_list_env(&program->env_vars);
	ft_free_array(&program->_var);
	ft_free_array(&program->input);
	ft_free_all(program);
}
