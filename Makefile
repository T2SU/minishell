# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/01 16:47:39 by smun              #+#    #+#              #
#    Updated: 2021/08/01 17:14:23 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

INC = -I./ -I/usr/local/opt/readline/include
LIB = -L/usr/local/opt/readline/lib -lreadline

TEST_SRC = test_readline \
			test_add_history \
			test_rl_redisplay
TEST_OUT = $(TEST_SRC:.c=.out)

%.out : %.c
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $<

test: $(addsuffix .out, $(TEST_SRC))

.PHONY: test
