# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skarayil <skarayil@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/15 11:00:00 by ybalkan           #+#    #+#              #
#    Updated: 2026/08/16 21:06:39 by skarayil         ###   ########.fr        #
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
			  sources/launch_utils.c \
			  sources/launch_utils_extra.c \
			  sources/launch_tests.c

OBJS		= $(OBJ_DIR)/load_test.o \
			  $(OBJ_DIR)/launch_utils.o \
			  $(OBJ_DIR)/launch_utils_extra.o \
			  $(OBJ_DIR)/launch_tests.o

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	$(RANLIB) $(NAME)

$(OBJ_DIR)/%.o: sources/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(NAME)

fclean: clean
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re
