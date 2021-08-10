# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/01 16:47:39 by smun              #+#    #+#              #
#    Updated: 2021/08/11 00:42:22 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

INC = -I./
LIB = -ltermcap

TEST_SRC = cursor0 \
			cursor1 \
			cursor2 \
			tty
TEST_OUT = $(addsuffix .out, $(TEST_SRC))

%.out : %.c
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $<

all: $(TEST_OUT)

clean:
	rm -rf $(TEST_OUT)

re: clean all

.PHONY: all clean re
