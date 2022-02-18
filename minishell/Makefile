# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvirgini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 15:15:50 by mvirgini          #+#    #+#              #
#   Updated: 2022/02/14 01:07:22 by mvirgini         ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

NAME_BONUS			=	minishell_bonus

DIR_MAIN			=	src/

DIR_BONUS			=	src_bonus/

HEADER_DIR			=	header/

HEADER_DIR_BONUS	=	header_bonus/

SRC_FILES	=	minishell.c \
					ft_create_delete_elem_list.c \
					ft_push_back_lst_list.c \
					ft_list_copy.c \
					ft_strjoin.c \
					ft_substr.c \
					ft_strdup.c \
					ft_strcmp.c \
					ft_parser_str.c \
					ft_parser_env.c \
					ft_env.c \
					ft_exit.c \
					ft_pwd.c \
					ft_unset.c \
					ft_export.c \
					ft_cd.c \
					ft_itoa.c \
					ft_echo.c \
					ft_str_error.c \
					ft_atoi.c \
					ft_pipex.c \
					ft_another_commands.c \
					ft_another_commands2.c \
					ft_export_one_variable.c \
					ft_path.c \
					ft_execute_command.c \
					ft_redirects.c \
					ft_redirects2.c \
					ft_redirects3.c \
					ft_here_doc.c \
					ft_signal_ctrl_c.c \
					ft_delete_tmp_files.c \
					ft_parser.c \
					ft_parser2.c \
					ft_duplicate_list.c \
					ft_sort_list.c \
					ft_parser_str2.c \
					ft_parser_str3.c \
					ft_here_doc2.c \
					ft_here_doc3.c \
					ft_pipex2.c \
					ft_pipex3.c \
					ft_pipex4.c \
					ft_pipex5.c \
					ft_another_commands3.c

SRC_BONUS	=	minishell_bonus.c \


OBJ_SRC = $(addprefix $(DIR_MAIN),$(SRC_FILES:.c=.o))

OBJ_BONUS = $(addprefix $(DIR_BONUS),$(SRC_BONUS:.c=.o))

CC = gcc

REM = rm -f

HEADER = $(HEADER_DIR)minishell.h

HEADER_BONUS = $(HEADER_DIR_BONUS)minishell_bonus.h

FLAGS_1 = -Wall -Wextra -Werror -I/usr/local/opt/readline/include

FLAGS_2 = -lreadline -L/usr/local/opt/readline/lib

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ_SRC)
			$(CC) $(OBJ_SRC) $(FLAGS_2) -o $(NAME)

%.o:	%.c $(HEADER)
			$(CC) -I$(HEADER_DIR) $(FLAGS_1) -c $< -o $@

bonus:
			@make HEADER_DIR="$(HEADER_DIR_BONUS)" OBJ_SRC="$(OBJ_BONUS)" HEADER="$(HEADER_BONUS)" NAME="$(NAME_BONUS)" all

clean:
	$(REM) $(OBJ_SRC) $(OBJ_BONUS)

fclean: clean
	$(REM) $(NAME) $(NAME_BONUS)

re: fclean all