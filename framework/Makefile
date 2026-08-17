# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/15 11:00:00 by ybalkan           #+#    #+#              #
#    Updated: 2026/08/17 20:36:32 by skarayil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ../libunit.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rc
RANLIB		= ranlib

INCLUDE		= -Iinclude
OBJ_DIR		= objects

SRCS		= sources/load_test.c \
			  sources/print_utils.c \
			  sources/signal_analyzer.c \
			  sources/launch_tests.c

OBJS		= $(OBJ_DIR)/load_test.o \
			  $(OBJ_DIR)/print_utils.o \
			  $(OBJ_DIR)/signal_analyzer.o \
			  $(OBJ_DIR)/launch_tests.o

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@$(RANLIB) $(NAME)

$(OBJ_DIR)/%.o: sources/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -f $(OBJ_DIR)/*.o $(NAME)

fclean: clean
	@rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re
