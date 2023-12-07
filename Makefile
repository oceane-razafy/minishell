# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:46:57 by aselnet           #+#    #+#              #
#    Updated: 2023/07/18 14:11:23 by aselnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -D BUFFER_SIZE=512
IFLAGS = -I$(INCDIR) -I$(LIBDIR)
LFLAGS = -lreadline -L$(LIBDIR) -lft

SRCDIR = srcs
OBJDIR = objs
BINDIR = bin
INCDIR = include
LIBDIR = libft

EXECDIR = execution
PARSINGDIR = parsing
BUILTINSDIR = builtins
SIGNALSDIR = signals

EXEC_FILES = free_heredoc.c \
			ft_all_redir.c \
			ft_close.c \
			ft_error_exec.c \
			ft_execute_bis.c \
			ft_execute.c \
			ft_exit_exec.c \
			ft_fill_cmd_type_r.c \
			ft_fill_cmd.c \
			ft_fork.c \
			ft_free_all_exec.c \
			ft_free_cmd.c \
			ft_get_cmd.c \
			ft_get_status.c \
			ft_init_cmd.c \
			heredoc.c \
			heredoc2.c \

PARSING_FILES = define.c \
				define2.c \
				define3.c \
				expand.c \
				expand2.c \
				expand3.c \
				expand4.c \
				lexing.c \
				lexing2.c \
				lexing3.c \
				parsing.c \
				parsing2.c \
				quit.c \
				tokens.c \
				tokens2.c \
				tokens3.c \

BUILTINS_FILES = ft_builtins_utils_2.c \
				ft_builtins_utils.c \
				ft_cd_utils.c \
				ft_cd.c \
				ft_echo.c \
				ft_env.c \
				ft_environment_utils_2.c \
				ft_environment_utils.c \
				ft_export_utils.c \
				ft_export.c \
				ft_pwd.c \
				ft_unset.c \
				ft_exit_utils.c \
				ft_exit.c

SIGNALS_FILES = ft_signals.c

EXEC = $(addprefix $(EXECDIR)/, $(EXEC_FILES))
PARSING = $(addprefix $(PARSINGDIR)/, $(PARSING_FILES))
BUILTINS = $(addprefix $(BUILTINSDIR)/, $(BUILTINS_FILES))
SIGNALS = $(addprefix $(SIGNALSDIR)/, $(SIGNALS_FILES))
SRCS = $(addprefix $(SRCDIR)/, minishell.c ft_init.c $(EXEC) $(PARSING) $(BUILTINS) $(SIGNALS))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCS = $(INCDIR)/minishell.h

NAME = $(BINDIR)/minishell

RMR = rm -rf
MKDIR_P = mkdir -p

LIBFT = $(LIBDIR)/libft.a

all: $(NAME)

$(LIBFT):
	cd $(LIBDIR) && make

$(NAME): $(OBJS) $(LIBFT) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) $(LIBS) $(LFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS) | $(OBJDIR)
	$(MKDIR_P) $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ 

$(BINDIR):
	$(MKDIR_P) $(BINDIR)

$(OBJDIR):
	$(MKDIR_P) $(OBJDIR)

clean:
		$(RMR) $(OBJDIR)
		cd $(LIBDIR) && make clean

fclean: clean
		$(RMR) $(BINDIR)
		cd $(LIBDIR) && make fclean

re: fclean all

.PHONY: all clean fclean re