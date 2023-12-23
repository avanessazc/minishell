/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:06:03 by ayzapata          #+#    #+#             */
/*   Updated: 2021/09/30 17:06:05 by ayzapata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include "../libft/libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <fcntl.h>
# include <strings.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <ctype.h>

# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define MAX_LONG 9223372036854775807
# define MIN_LONG -9223372036854775808

# define CONTINUE 42

# define CTRL_D_HEREDOC 21
# define CTRL_C_HEREDOC 22

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define READ 0
# define WRITE 1
# define YES 1
# define NO 0
# define ALIVE 0
# define KILL 1

# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
# define DOLLAR_SYMBOL 30
# define DOLLAR_QUESTION_SYMBOLS 40
# define QUOTE_DOUBLE_TO_DELETE 5
# define QUOTE_SIMPLE_TO_DELETE 6
# define EXPANSION_VAR 7
# define EXPANSION_EXIT_CODE 8
# define BETWEEN_QUOTES 9
# define EXPANSION_VAR_BETWEEN_QUOTES 3
# define EXPANSION_EXIT_CODE_BETWEEN_QUOTES 4

# define DOLLAR 1
# define ESPACE 1
# define EQUAL_SYMBOL 1
# define QUESTION_SYMBOL 1

# define SUCCESS 0
# define ERR_ARGUMENTS -1
# define ERR_QUOTE -2
# define ERR_MALLOC -3
# define ERR_PARSER -4
# define ERR_ENV_VAR -5
# define ERR_GET_CWD -6
# define ERR_PIPE -7
# define ERR_FORK -8
# define ERR_CHDIR -9
# define ERR_OPENDIR -10
# define ERR_CLOSEDIR -11
# define HOME_NOT_SET -12

/*
**	Tokens clasification
*/
# define PIPE_TYPE 1
# define COMMAND_TYPE 2
# define REDIR_INFILE_TYPE 3
# define REDIR_LIMITER_TYPE 4
# define REDIR_OUTFILE_TYPE 5
# define REDIR_APPEND_TYPE 6

typedef struct s_ie
{
	int		init;
	int		end;
}					t_ie;

/*
** type		->	tokens clasification. see the defines
** qtdae	->	quotes to delete after expander
** nq		->	array without quotes
*/
typedef struct s_list
{
	int				id;
	char			*line;
	int				type;
	int				*qtdae;
	int				*nq;
	int				check_equal;
	int				check_export;
	int				check_cd;
	struct s_list	*next;
}					t_list;

typedef struct s_env
{
	int				id;
	char			*str;
	char			*name;
	int				len_name;
	int				equals_symbol;
	char			*value;
	int				len_value;
	int				print;
	struct s_env	*next;
}					t_env;

typedef struct s_args
{
	char	**args;
	int		*type;
	int		size;
}				t_args;

typedef struct s_pipe
{
	int			fd[2];
}				t_pipe;

typedef struct s_program
{
	int				flag_env_i;
	int				std_in;
	int				std_out;
	t_list			*token;
	t_env			*env_vars;
	char			**envp;
	int				exit;
	char			*old_input;
	int				pipes_nbr;
	int				shlvl;
	t_args			*args_lst;
	t_ie			*limits;
	t_pipe			*pipes;
	int				children;
	int				*to_delete;
	pid_t			*processes;
	int				*launched_children;
	int				*processes_exit_codes;
	pid_t			delimiter_process;
	t_pipe			*fd_delimiter;
	char			**clean_args;
	int				counter_infile;
	int				counter_outfile;
	int				counter_delimiter;
	int				fd_infile;
	int				fd_outfile;
	char			*_var;
	int				last_delimiter;
	int				flag_infile;
	char			*input_heredoc;
	char			*input;
	char			*delimiter;
	char			*exit_code_array;
	int				exit_code_len;
	int				ctrl_c_heredoc;
	int				exit_code;
	int				flag_print_nl;
}					t_program;

t_program		*g_prog;

typedef struct s_cd
{
	DIR		*rep;
	char	*cur_dir;
	char	*pwd;
	char	*oldpwd;
	char	*home;
	char	*cdpath;
	char	*ext_path_a;
	char	*ext_path_b;
	char	*tmp;
	int		flag_minus;
	int		flag_print_dir;
	int		flag_path_a;
	int		flag_path_b;
	char	ret;
	char	*err_msg;
}				t_cd;

typedef struct s_next_text_len
{
	int		t;
	int		var_len;
	int		new_text_len;
	int		found;
	t_env	*tmp;
}				t_next_text_len;

typedef struct s_create_new_line
{
	int				i;
	int				j;
	int				len;
	int				new_line_len;
	char			*new_line;
	int				flag;
}				t_create_new_line;

typedef struct s_se
{
	int		start;
	int		end;
}				t_se;

typedef struct s_line_after_quotes
{
	int		i;
	int		flag;
	char	*new_line;
	int		new_line_len;
	int		len;
	int		j;
	int		k;
}				t_line_after_quotes;

typedef struct s_expanded_var_to_token
{
	int		i;
	t_list	*token;
	int		start;
	int		end;
	t_list	*tmp;
	int		len;
}				t_expanded_var_to_token;

typedef struct s_env_var_to_list
{
	int		i;
	int		id;
	int		ret;
}				t_env_var_to_list;

typedef struct s_get_tokens
{
	int		i;
	int		start;
	int		end;
	int		ret;
	int		j;
}				t_get_tokens;

void	ft_title(void);
void	ft_start(t_program *program, char *envp[]);
int		ft_history_manager(t_program *program, char *input);
int		minishell(t_program	*program, char **envp[]);
char	**ft_env_to_array(t_program *program);

/*
**		ft_frees1.c
*/
void	ft_free_array(char **to_free);
void	ft_free_array_int(int **to_free);
void	ft_free_array_pipe(t_pipe **to_free);
void	ft_free_array_processes(pid_t **to_free);
void	ft_free_array2(char **to_free);

/*
**		ft_frees2.c
*/
int		ft_ie_struct(t_ie **to_free);
int		ft_free_args_struct(t_args **to_free, int len);
void	ft_free_history(t_program *program);
void	ft_free_multi_arrays(char **str1, char **str2, char **str3, \
char **str4);

/*
**		ft_frees3.c
*/
void	ft_free_all(t_program *program);
void	ft_free_program(t_program *program);
void	ft_free_before_execute_cmd(t_program *program);
void	ft_free_before_execute_builtin(t_program *program);
void	ft_free_ctro_d_heredoc(t_program *program);

/*
**		/parsing/ft_list_utils_tokens.c
*/
t_list	*ft_new_elem(int id);
int		ft_add_new_elem(t_list **cmd, int id);
void	ft_clear_list(t_list **to_free);
int		ft_list_size(t_list *lst);

/*
**		/parsing/ft_list_utils_env.c
*/
t_env	*ft_new_elem_env(int id, char *str);
int		ft_add_new_elem_env(t_env **env, int id, char *str);
void	ft_clear_list_env(t_env **to_free);
int		ft_list_size_env(t_env *lst);

/*
**		/parsing/ft_check_angle_brackets.c
*/
int		ft_check_angle_brackets(t_program *program, int i);

/*
**		/parsing/ft_split_by_angle_brackets.c
*/
int		ft_split_by_angle_brackets(t_list **token, \
t_list **tmp, int *start, int *i);

/*
**		/parsing/ft_get_tokens.c
*/
int		ft_get_tokens(t_program *program, int id);

/*
**		/parsing/ft_env_var_to_list.c
*/
int		ft_env_var_to_list(t_env **env_var, char **env);
int		ft_set_env_list_node(t_env **tmp, int i);

/*
**		/parsing/ft_split_by_spaces.c
*/
int		ft_split_by_spaces(t_program *program, char *str, int id);

/*
**		/parsing/ft_parser_tokens_utils.c
*/
int		ft_check_quotes(char *str, char c, int *i);
int		ft_quotes(char *str, int *i);
int		ft_get_sub_line(t_list **list, char *str, int start, int len);

/*
**		/parsing/ft_parser_tokens.c
*/
int		ft_split_by_pipe_and_point_comma_symbol(t_list **token,
			t_list **tmp, int *start, int *i);
int		ft_check_pipe_and_point_comma_symbols(t_program *program);
int		ft_check_pipe_point_comma_and_angle_brackets_symbols(
			t_program *program);
void	ft_classify_tokens(t_program *program);
int		ft_parser_tokens(t_program *program, char *str, int id);

/*
**		/expander/ft_expander.c
*/
int		ft_expander(t_program *program, int len);
int		ft_expander_utils(t_program *program);
int		ft_get_new_line(t_program *program, int len, t_list	**tmp);
int		ft_delete_quotes(t_program *program);

/*
**		/expander/ft_expander_utils1.c
*/
int		*ft_create_array_int(int len, int value);
void	ft_classify_quotes(int **quotes, char *line, int i, int t);
int		ft_find_quote_zones(int **quotes, char *line, int len);
int		ft_find_dollar_symbols(int **quotes, char *line, int len);
int		ft_portable_expanser(t_program *program, char *line, char **new_line);

/*
**		/expander/ft_expander_utils2.c
*/
int		ft_find_equal_symbol(t_program *program);
int		ft_find_export_cmd(t_program *program);
int		ft_find_export_args(t_program *program);
int		ft_find_cd_cmd(t_program *program);
int		ft_find_cd_args(t_program *program);
/*
**		/expander/ft_expander_utils3.c
*/
char	*ft_line_after_delete_quotes(char *line, int *qtdae, int **nq);

/*
**		/expander/ft_expander_utils4.c
*/
int		ft_split_expanded_var(t_program *program, int id);
void	ft_set_id(int id, t_list **token);
/*
**		/expander/ft_expander_utils5.c
*/
int		ft_delete_quote_spaces(t_program *program, int len, int i, t_list *tmp);
int		ft_delete_quote_spaces_a(t_list **tmp, int i, int c, int j);
int		ft_delete_quote_spaces_a_util(t_list **tmp, char **new_line, \
int *i, int *j);
int		ft_new_token(t_list	**token, t_list	*tmp, int start, int end);
int		ft_new_token_util(t_list **tempo, t_list *tmp, int len, int start);

/*
**		/expander/ft_expander_utils6.c
*/
void	ft_avance(t_expanded_var_to_token *evtt);
void	ft_init_var_evtt(t_expanded_var_to_token *evtt);
int		is_equal(int a, int b);
int		ft_count_quotes_to_delete_util(int *quotes, int len, int *i, int *flag);
int		ft_count_quotes_to_delete(int *quotes, int len);

/*
**		/expander/ft_expander_utils7.c
*/
int		ft_expanded_var_to_token_util(t_expanded_var_to_token *evtt);
int		ft_case_one(t_expanded_var_to_token *evtt);
int		ft_expanded_var_to_token_util_bis(t_expanded_var_to_token *evtt);
int		ft_expanded_var_to_token_util_ter(t_expanded_var_to_token *evtt);
int		ft_expanded_var_to_token(t_program *program, int id);

/*
**		/expander/ft_expander_utils8.c
*/
void	ft_avance(t_expanded_var_to_token *evtt);
void	ft_init_var_evtt(t_expanded_var_to_token *evtt);
int		is_equal(int a, int b);

/*
**		/expander/ft_new_line_length.c
*/
int		ft_is_env_var_char(int c);
int		ft_new_line_length(t_program *program, char *line,
			int *quotes, int len);
int		ft_exit_code_to_array(t_program *program);

/*
**		/expander/ft_create_new_line.c
*/
char	*ft_create_new_line(t_program *program,
			char *line, int *quotes, int **qtdae);

/*
**		/expander/ft_create_new_line_utils.c
*/
int		ft_exit_code_expander(t_create_new_line *cnl, \
char *exit_code_array, int **qtdae);
int		ft_env_var_expander_util(t_create_new_line *cnl, \
t_env *tmp, int **qtdae);
int		ft_env_var_expander(t_program *program, char *line, \
t_create_new_line *cnl, int **qtdae);
int		ft_init_var(t_create_new_line *cnl, char *line, \
t_program *program, int *quotes);
int		ft_init_var_bis(t_create_new_line *cnl, int **qtdae);

/*
**		/builtins
*/
int		ft_echo(char **args);
int		ft_env(t_env *env, t_program *program, char **args);
int		ft_pwd(t_program *program);
int		ft_unset(t_program *program, char **args);
int		ft_export(t_program *program, char **args, int i, int len);
int		ft_cd(t_program *program, char **args[]);
int		ft_update_shlvl(t_program *program, int change);
int		ft_set(t_program *program, char *var_name, char *value);

/*
**		/builtins/ft_cd_utils1.c
*/
int		ft_update_shlvl(t_program *program, int change);
int		count_args(char **array);
void	print_two_str(char *str1, char *str2, int fd);
int		print_e(char **args[], char *err, int exit_code, int option);
int		print_e_bis(char **args[], char *err, int exit_code);

/*
**		/builtins/ft_cd_utils2.c
*/
int		ft_cd_minus(t_cd *cd, char **args[], t_program *program);
int		ft_cd_empty(char **args[]);
int		ft_cd_without_args(t_cd *cd, char **args[], t_program *program);
int		ft_cd_minus_empty_no_args(t_cd *cd, char **args[], t_program *program);
int		ft_get_cdpath(t_cd *cd, char **args[], t_program *program);

/*
**		/builtins/ft_cd_utils3.c
*/
int		print_e_ter(char *arg, char *err, int exit_code);
int		ft_replace_args(t_cd *cd, char **args[]);
int		ft_check_pwd_and_set_oldpwd(t_cd *cd, char **args[], \
t_program *program);
void	ft_add_cdpath(t_cd *cd, char **args[]);
void	ft_free_ext_path_a(t_cd *cd);

/*
**		/builtins/ft_exit.c
*/
int		ft_exit(char **args, int *exit_cmd, int pipes_nbr, t_program *program);
void	ft_more_then_two_args(char **args, int len, \
int *exit_cmd, int pipes_nbr);
void	ft_zero_args(int len, int *exit_cmd, int pipes_nbr);	
void	ft_exit_code_two(char **args, int *exit_cmd, int pipes_nbr);
void	pipes_nbr_equal_zero(int *exit_cmd, int pipes_nbr, int option);

/*
**		/builtins/ft_export_utils1.c
*/
int		ft_env_sorted(t_env *env);

/*
**		/builtins/ft_export_utils2.c
*/
int		ft_print_export_list(t_env *env);

/*
**		/builtins/ft_export_utils3.c
*/
int		case_error(char *str, int j, int *error);
int		case_a_not_found(t_program *program, t_env **tmp, char *str, int j);

/*
**		/builtins/ft_exit_utils.c
*/
void	ft_two_args(char **args, int len, int *exit_cmd, int pipes_nbr);
void	set_exit_code(int neg, unsigned long long value, \
int *exit_cmd, int pipes_nbr);
void	get_value(char **args, int neg, \
unsigned long long *value);					
void	is_negative(char **args, int *neg, int *i);						
void	if_negative_or_positive(int neg, unsigned long long value);

/*
**		/execution/ft_set_pipes.c
*/
int		ft_count_pipes(t_list *token);
int		ft_pipes_mallocs(t_program *program);
void	pipes_first_cmd(int process, t_program *program);
void	pipes_between_zero_and_last_cmd(int process, t_program *program);
void	pipes_last_cmd(int process, t_program *program);

/*
**		/execution/ft_child_process.c
*/
void	ft_execve(char **path, char **cmd, char **env, t_program *program);
void	ft_execute_command(char *env[], t_program *program);
void	ft_execute_builtin(t_program *program);
void	ft_child_process(char *env[], int process, t_program *program, \
int error);

/*
**		/execution/ft_child_process_utils.c
*/
void	check_command(char **cmd, t_program *program);
void	print_msg_err_path_cmd(char **cmd, char *msg);
int		check_path_cmd(char **path, char **cmd, t_program *program, int fd);
int		check_file_descriptor(int fd, char *file_name);
void	check_if_path_exist(int ret, t_program *program, char *path_var);

/*
**		/execution/pipex.c
*/
void	ft_set_exit_code_last_cmd(t_program *program);
int		ft_create_children(t_program *program, int *error, int *i);
int		ft_execution_more_than_one_command(t_program *program, int *error);
int		pipex(t_program *program, int error);

/*
**		/execution/pipex_utils.c
*/
int		ft_get_env(t_env *env, char *var, char **value);
void	check_str(char *str, char **path, t_program *program);
void	ft_get_cmd(char **path, char **cmd[], t_program *program, int i);
int		ft_is_built_in(char	*str, t_env *env);
int		ft_exec_built_in(t_program *program, char **args[]);

/*
**		/execution/ft_wait_children.c
*/
void	ft_close_pipes(t_program *program);
int		ft_save_processes_exit_codes(t_program *program, int k, int status);
void	ft_wait_children(t_program *program);

/*
**		/execution/ft_launch_children.c
*/
void	check_minishell_cmd(t_program *program);
void	ft_set_envp(t_program *program);
int		ft_launch_children(t_program *program, int i, int error);

/*
**		/execution/ft_execution_one_command.c
*/
void	ft_redirect_fdinfile_fdoutfile_one_command(t_program *program, \
int *error);
int		ft_clean_args(t_program *program, int process);
void	check_clean_args(t_program *program, int i);
int		ft_execution_one_command(t_program *program, int *error);

/*
**		/execution/ft_tokens_to_array.c
*/
int		ft_tokens_to_array(t_program *program);
int		ft_tokens_to_array_util(t_program *program, int *i, \
t_list **tmp, int j);

/*
**		/execution/ft_find_pipes_limits.c
*/
int		ft_find_pipes_limits(t_program *program);

/*
**		/execution/ft_heredoc_utils.c
*/
void	ft_display_err_free_program(char *err, t_program *program, int option);
void	ft_push_expand_hline_to_delim_pipe(t_program *program, char **new_line);
void	ft_free_array_and_fill_to_delete(t_program *program, int j);

/*
**		/execution/ft_heredoc.c
*/
int		ft_malloc_delim_pipe_first_heredoc(t_program *program, int process, \
int j);
int		ft_get_heredoc_lines(t_program *program, int j, int process, \
char *new_line);
int		ft_loop_intermediary_heredocs(t_program *program, int *j);
int		ft_launch_heredoc_check_for_delim(t_program *program, int *j, \
int process);

/*
**		ft_signals.c
*/
void	sig_int(int signum);
void	signal_ctrl_d_father(t_program *program, char **envp[]);
void	sig_int_child(int signum);

/*
**		ft_errors.c
*/
int		ft_error(t_program *program, int err);
void	check_main_args(int argc);

/*
**		ft_init.c
*/
void	ft_init_cd(t_cd *cd);
void	ft_init_program(t_program *program);
void	ft_re_init_program(t_program *program);

/*
**		ft_settings.c
*/
void	ft_unset_oldpwd(t_program *program);
int		set_env_var(t_program *program, char **envp[], int ret);
void	set__var(t_program *program);
int		set_terminal(t_program *program);

/*
**		/execution/ft_redirections.c
*/
int		ft_redirections(t_program *program, int process, int *error, int ret);
int		ft_redir_outfile_append(t_program *program, int *j, int process, \
int *error);
int		ft_redir_infile_delimiter(t_program *program, int *j, \
int process, int *error);
/*
**		/execution/ft_redirections_utils.c
*/
void	ft_redirect_fdinfile_fdoutfile(t_program *program, int error);
int		ft_count_new_size(int *array, int len);
int		ft_open_infile_check_fd(t_program *program, int *j, int process, \
int *error);
int		ft_count_delimiter(char **str, char *delimiter, int *last_delimiter, \
int count);

#endif
