# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayzapata <ayzapata@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 17:05:55 by ayzapata          #+#    #+#              #
#    Updated: 2021/10/05 17:44:25 by ayzapata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDES := -I./includes

SRCS := \
		srcs/builtins/ft_cd.c \
		srcs/builtins/ft_cd_utils1.c \
		srcs/builtins/ft_cd_utils2.c \
		srcs/builtins/ft_cd_utils3.c \
		srcs/builtins/ft_echo.c \
		srcs/builtins/ft_env.c \
		srcs/builtins/ft_pwd.c \
		srcs/builtins/ft_set.c \
		srcs/builtins/ft_unset.c \
		srcs/builtins/ft_export.c \
		srcs/builtins/ft_exit.c \
		srcs/builtins/ft_exit_utils.c \
		srcs/builtins/ft_export_utils1.c \
		srcs/builtins/ft_export_utils2.c \
		srcs/builtins/ft_export_utils3.c \
		srcs/execution/pipex.c \
		srcs/execution/pipex_utils.c \
		srcs/execution/ft_child_process.c \
		srcs/execution/ft_child_process_utils.c \
		srcs/execution/ft_child_process_utils2.c \
		srcs/execution/ft_child_process_utils3.c \
		srcs/execution/ft_child_process_utils4.c \
		srcs/execution/ft_redirections.c \
		srcs/execution/ft_redirections_utils.c \
		srcs/execution/ft_set_pipes.c \
		srcs/execution/ft_wait_children.c \
		srcs/execution/ft_launch_children.c \
		srcs/execution/ft_execution_one_command.c \
		srcs/execution/ft_tokens_to_array.c \
		srcs/execution/ft_find_pipes_limits.c \
		srcs/execution/ft_heredoc.c \
		srcs/execution/ft_heredoc_utils.c \
		srcs/parsing/ft_env_var_to_list.c \
		srcs/parsing/ft_history_manager.c \
		srcs/parsing/ft_list_utils_tokens.c \
		srcs/parsing/ft_list_utils_env.c \
		srcs/parsing/ft_check_angle_brackets.c \
		srcs/parsing/ft_split_by_angle_brackets.c \
		srcs/parsing/ft_get_tokens.c \
		srcs/parsing/ft_parser_tokens.c \
		srcs/parsing/ft_split_by_spaces.c \
		srcs/parsing/ft_parser_tokens_utils.c \
		srcs/expander/ft_new_line_length.c \
		srcs/expander/ft_create_new_line.c \
		srcs/expander/ft_create_new_line_utils.c \
		srcs/expander/ft_expander.c \
		srcs/expander/ft_expander_utils1.c \
		srcs/expander/ft_expander_utils2.c \
		srcs/expander/ft_expander_utils3.c \
		srcs/expander/ft_expander_utils4.c \
		srcs/expander/ft_expander_utils5.c \
		srcs/expander/ft_expander_utils6.c \
		srcs/expander/ft_expander_utils7.c \
		srcs/expander/ft_expander_utils8.c \
		srcs/ft_settings.c \
		srcs/ft_settings_utils.c \
		srcs/ft_init.c \
		srcs/ft_title.c \
		srcs/ft_frees1.c \
		srcs/ft_frees2.c \
		srcs/ft_frees3.c \
		srcs/ft_frees4.c \
		srcs/ft_signals.c \
		srcs/ft_errors.c \
		srcs/minishell.c
		
CC = gcc

UNAME = $(shell uname)

ifeq (${UNAME}, Darwin)
OS = 1
LIBINC = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
INCLUDE_READLINE = -I/Users/$(USER)/.brew/opt/readline/include
endif

ifeq (${UNAME}, Linux)
OS = 0
LIBINC = -lreadline
endif

SRCS_DIR = $(addprefix $(DIR), $(SRCS))

OBJS = $(SRCS:.c=.o) 
CFLAGS = -g -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C ./libft/
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) -L ./libft -lft $(LIBINC)

%.o: %.c
			@mkdir -p $(@D)
			$(CC) $(CFLAGS) $(INCLUDE_READLINE) $(INCLUDES) -c $< -o $@

clean :
			@make clean -C ./libft/
			rm -rf $(OBJS)

fclean : clean
			@make fclean -C ./libft/
			rm -rf $(NAME)
			
re : fclean all

.PHONY: re, clean, fclean, all
