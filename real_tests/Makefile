# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skarayil <skarayil@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/15 11:00:00 by ybalkan           #+#    #+#              #
#    Updated: 2026/08/16 21:20:34 by skarayil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDE		= -I../framework/include

LIB		= ../libunit.a
BIN		= real_test_binary

SRCS		= ft_atoi.c \
			  main.c \
			  ft_atoi/00_launcher.c \
			  ft_atoi/01_basic_positive.c \
			  ft_atoi/02_basic_negative.c \
			  ft_atoi/03_zero.c \
			  ft_atoi/04_leading_spaces.c \
			  ft_atoi/05_all_whitespace_chars.c \
			  ft_atoi/06_plus_sign.c \
			  ft_atoi/07_negative_zero.c \
			  ft_atoi/08_int_max.c \
			  ft_atoi/09_int_min.c \
			  ft_atoi/10_number_then_alpha.c \
			  ft_atoi/11_alpha_then_number.c \
			  ft_atoi/12_only_whitespace.c \
			  ft_atoi/13_empty_string.c \
			  ft_atoi/14_only_plus_sign.c \
			  ft_atoi/15_only_minus_sign.c \
			  ft_atoi/16_ws_negative_ws.c \
			  ft_atoi/17_leading_zeros.c

all: $(BIN)

$(LIB):
	$(MAKE) -C ../framework

$(BIN): $(LIB)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -L.. -lunit -o $(BIN)

test: $(BIN)
	-./$(BIN)

clean:
	rm -f $(BIN)

fclean: clean

re: fclean all

.PHONY: all clean fclean re test
