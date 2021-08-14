CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

ROOT_PATH = .
SRCS = $(ROOT_PATH)/something.c
OBJ = $(SRCS:.c=.o)

# Default macOS brew package installation path.
READLINE_ROOT = /usr/local/opt/readline

# Install package 'readline-devel'.
ifeq ($(shell uname -s), Linux)
	READLINE_ROOT = /usr
endif

INC = -I$(ROOT_PATH)/includes
LIB = -L$(READLINE_ROOT)/lib -lreadline -lhistory -ltermcap
NAME = minishell

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all clean re fclean
