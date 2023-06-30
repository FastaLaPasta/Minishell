# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgiampor <jgiampor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/22 12:59:05 by sboulogn          #+#    #+#              #
#    Updated: 2023/06/22 15:22:02 by jgiampor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEAD = ft_minishell.h
SRCS = ft_minishell.c parse.c Builtins/cd.c Builtins/echo.c Builtins/env.c \
		Builtins/pwd.c Builtins/unset.c Builtins/exit.c parse_utils.c \
		parse_utils_2.c Builtins/export.c errors_utils.c ft_lstlast.c \
		ft_lstnew.c ft_lstadd_back.c ft_analize.c ft_clearchevron.c ft_exec.c\
		ft_free.c ft_utils.c ft_strlen_mallocsize.c ft_fill_quotes.c \
		ft_analize2.c ft_verif_syntax.c ft_true_file.c ft_true_file_utils.c\
		ft_exec_2.c Builtins/export_utils.c ft_utils_test_man.c ft_exec_3.c

LIB = Libft/libft.a
LDFLAGS = -L/Users/$$USER/.brew/opt/readline/lib
CPPFLAGS = -I/Users/$$USER/.brew/opt/readline/include
			
OBJ = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

.c.o :
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(MAKE) -C Libft
	$(CC) $(LDFLAGS) $(CPPFLAGS) $(LIB) -lreadline -o $(NAME) $(OBJ)

clean:
	$(MAKE) clean -C Libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C Libft
	rm -f $(NAME)
	
bonus: all

re: fclean all