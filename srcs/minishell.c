/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:18:25 by abesombe          #+#    #+#             */
/*   Updated: 2021/10/05 18:07:12 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_to_array(t_program *program)
{
	char	**arg;
	t_env	*tmp;
	int		len;
	int		i;

	len = ft_list_size_env(program->env_vars);
	arg = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arg)
		return (NULL);
	tmp = program->env_vars;
	i = 0;
	while (tmp && i < len)
	{
		arg[i] = ft_strdup(tmp->str);
		if (!arg[i])
		{
			ft_free_array2(arg);
			arg = NULL;
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	arg[i] = NULL;
	return (arg);
}

int	check_parsing(t_program *program)
{
	int	ret;

	ret = ft_parser_tokens(program, program->input, 1);
	if (ret == ERR_MALLOC)
	{
		ft_free_array(&program->input);
		ft_free_program(program);
		ft_error(program, ERR_MALLOC);
		exit(1);
	}
	if (ret != ERR_MALLOC && ret != 0)
	{
		ret = ft_history_manager(program, program->input);
		ft_free_array(&program->input);
		ft_free_all(program);
		ft_re_init_program(program);
		return (CONTINUE);
	}
	return (0);
}

void	execution(t_program *program, int ret)
{
	ret = ft_history_manager(program, program->input);
	if (ret == ERR_MALLOC)
	{
		ft_free_program(program);
		ft_error(program, ERR_MALLOC);
		exit(1);
	}
	if (ret != ERR_MALLOC && ret == 0)
	{
		program->pipes_nbr = ft_count_pipes(program->token);
		ret = ft_expander(program, 0);
		if (ret == ERR_MALLOC)
		{
			ft_free_program(program);
			ft_error(program, ERR_MALLOC);
			exit(1);
		}
		ret = pipex(program, 0);
		if (ret == ERR_MALLOC || ret == ERR_PIPE || ret == ERR_FORK)
		{
			ft_free_program(program);
			ft_error(program, ret);
			exit(1);
		}
	}
}

int	minishell(t_program	*program, char **envp[])
{
	if (ft_exit_code_to_array(program) == ERR_MALLOC)
	{
		ft_free_array(&program->input);
		ft_free_program(program);
		ft_error(program, ERR_MALLOC);
		exit(g_prog->exit_code);
	}
	program->input = readline("MS$ ");
	signal_ctrl_d_father(program, envp);
	if (ft_strcmp(program->input, "") == 0)
	{
		ft_free_array(&program->input);
		return (CONTINUE);
	}
	if (check_parsing(program) == CONTINUE)
		return (CONTINUE);
	execution(program, 0);
	ft_free_all(program);
	ft_re_init_program(program);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_program	program;
	int			ret;

	(void)argv;
	ft_init_program(&program);
	ret = set_env_var(&program, &envp, 0);
	if (ret != 0)
		return (ft_error(&program, ret));
	check_main_args(argc);
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, SIG_IGN);
	g_prog = &program;
	ft_unset_oldpwd(&program);
	set__var(&program);
	ft_start(&program, envp);
	set_shlvl_var(&program, NULL);
	while (program.exit == 0)
		minishell(&program, &envp);
	if (program.flag_env_i == 1)
	{
		ft_free_array(&(envp[0]));
		free(envp);
	}
	ft_free_program(&program);
	return (g_prog->exit_code);
}
