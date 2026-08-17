# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/15 11:00:00 by ybalkan           #+#    #+#              #
#    Updated: 2026/08/17 20:56:52 by skarayil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDE		= -I../framework/include

LIB		= ../libunit.a
BIN		= test_binary

SRCS		= main.c \
		  dummy_tests/00_launcher.c \
		  dummy_tests/01_ok_test.c \
		  dummy_tests/02_ko_test.c \
		  dummy_tests/03_segv_test.c \
		  dummy_tests/04_bus_test.c \
		  dummy_tests/05_abort_test.c \
		  dummy_tests/06_fpe_test.c \
		  dummy_tests/07_pipe_test.c \
		  dummy_tests/08_ill_test.c \
		  dummy_tests/09_timeout_test.c

all: $(BIN)

$(LIB):
	@$(MAKE) -C ../framework

$(BIN): $(LIB)
	@$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -L.. -lunit -o $(BIN)

test: $(BIN)
	-./$(BIN)

clean:
	@rm -f $(BIN)

fclean: clean

re: fclean all

.PHONY: all clean fclean re test
