# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/01 16:47:39 by smun              #+#    #+#              #
#    Updated: 2021/09/01 13:14:53 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Default macOS brew package installation path.
READLINE_ROOT = /usr/local/opt/readline

# Install package 'readline-devel'.
ifeq ($(shell uname -s), Linux)
	READLINE_ROOT = /usr
endif

ifeq ($(shell uname -s), Darwin)
#	Apple silicon 칩셋에서는 Rosetta 2로 구동될 수 있게끔 x86_64로 크로스 컴파일
	ifeq ($(shell uname -m), arm64)
		CFLAGS += -target x86_64-darwin-macho
	endif
endif


INC = -I./ -I$(READLINE_ROOT)/include
LIB = -L$(READLINE_ROOT)/lib -lreadline -lhistory -ltermcap

TEST_SRC = readline \
			add_history \
			new_prompt \
			heredoc
TEST_OUT = $(addsuffix .out, $(TEST_SRC))

%.out : %.c
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $<

all: $(TEST_OUT)

clean:
	rm -rf $(TEST_OUT)

re: clean all

.PHONY: all clean re
