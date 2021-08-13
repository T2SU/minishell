# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/01 16:47:39 by smun              #+#    #+#              #
#    Updated: 2021/08/14 02:31:17 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

ROOT_PATH = ../..
LIBSRCS = $(wildcard $(ROOT_PATH)/lib/srcs/list/*.c) \
			$(wildcard $(ROOT_PATH)/lib/srcs/strbuf/*.c) \
			$(wildcard $(ROOT_PATH)/lib/srcs/libft/memory/*.c) \
			$(wildcard $(ROOT_PATH)/lib/srcs/libft/string/*.c) \
			$(wildcard $(ROOT_PATH)/lib/srcs/error/*.c) \
			$(wildcard $(ROOT_PATH)/srcs/*.c) \
			$(wildcard $(ROOT_PATH)/srcs/lex/*.c)
LIBOBJ = $(LIBSRCS:.c=.o)

# Default macOS brew package installation path.
READLINE_ROOT = /usr/local/opt/readline

# Install package 'readline-devel'.
ifeq ($(shell uname -s), Linux)
	READLINE_ROOT = /usr
endif

INC = -I$(ROOT_PATH)/includes -I$(ROOT_PATH)/lib/includes -I./ -I$(READLINE_ROOT)/include
LIB = -L$(READLINE_ROOT)/lib -lreadline -lhistory -ltermcap

TEST_SRC = ast
TEST_OBJ = $(addsuffix .o, $(TEST_SRC))
TEST_OUT = $(addsuffix .out, $(TEST_SRC))

all: $(TEST_OUT)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(TEST_OUT): $(TEST_OBJ) $(LIBOBJ)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^

clean:
	rm -rf $(TEST_OUT)

re: clean all

.PHONY: all clean re
