CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

ROOT_PATH = .
SRCS = context \
		main \
		variable \
		strbuf/strbuf_append \
		strbuf/strbuf_get \
		syntax/tokenizer \
		syntax/syntax_clean \
		syntax/syntax_parser_command \
		syntax/syntax_parser_job \
		syntax/syntax_parser_statement \
		syntax/syntax_parser_word \
		syntax/syntax_parser \
		syntax/syntax_print

SRCS_FULL = $(addsuffix .c, $(addprefix $(ROOT_PATH)/srcs/, $(SRCS)))
OBJ = $(SRCS_FULL:.c=.o)

# Default macOS brew package installation path.
READLINE_ROOT = /usr/local/opt/readline

# Libft path
LIBFT_ROOT = $(ROOT_PATH)/libft

# Install package 'readline-devel'.
ifeq ($(shell uname -s), Linux)
	READLINE_ROOT = /usr
endif

INC = -I$(ROOT_PATH)/includes -I$(LIBFT_ROOT)
LIB = -L$(READLINE_ROOT)/lib -L$(LIBFT_ROOT) -lreadline -lhistory -ltermcap -lft
NAME = minishell

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ)
	@make -C $(LIBFT_ROOT) bonus
	$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^

clean:
	@make -C $(LIBFT_ROOT) clean
	rm -rf $(OBJ)

fclean: clean
	@make -C $(LIBFT_ROOT) fclean
	rm -rf $(NAME)

re: clean all

.PHONY: all clean re fclean
