# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/01 16:47:39 by smun              #+#    #+#              #
#    Updated: 2021/08/02 23:31:34 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

READLINE_ROOT = /usr/local/opt/readline
ifeq ($(shell uname -s), Linux)
	READLINE_ROOT = /usr
endif

INC = -I./ -I$(READLINE_ROOT)/include
LIB = -L$(READLINE_ROOT)/lib -lreadline -lhistory -ltermcap

TEST_SRC = readline \
			add_history \
			new_prompt
TEST_OUT = $(addsuffix .out, $(TEST_SRC))

%.out : %.c
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $<

all: $(TEST_OUT)

clean:
	rm -rf $(TEST_OUT)

re: clean all

.PHONY: all clean re
