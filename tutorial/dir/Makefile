# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/01 16:47:39 by smun              #+#    #+#              #
#    Updated: 2021/08/10 20:13:03 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

INC = -I./
LIB =

TEST_SRC = opendir
TEST_OUT = $(addsuffix .out, $(TEST_SRC))

%.out : %.c
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $<

all: $(TEST_OUT)

clean:
	rm -rf $(TEST_OUT)

re: clean all

.PHONY: all clean re
