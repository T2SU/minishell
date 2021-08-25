CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Debug Compilation Flags
# 나중에 제출 등에서는 아래 조건의 코멘트를 해제하여 기본적으로는 디버깅용 CFLAGS가 추가되지 않도록 해야함.
# ifeq ($(DEBUG),1)
	CFLAGS += -g -DVERBOSE=1
# -fsanitize=address
# endif

ROOT_PATH = .
SRCS = \
		main \
		variable \
		safe_memory \
		context/context \
		context/ft_basename \
		context/ft_random \
		shell/shell \
		shell/signal \
		execution/execution_heredoc \
		execution/execution_redirection \
		execution/execution \
		strbuf/strbuf_append \
		strbuf/strbuf_get \
		stack/stack \
		syntax/dispose_atom \
		syntax/dispose_property \
		syntax/tokenizer \
		syntax/tokenizer_word \
		syntax/tokenizer_print \
		syntax/syntax_grammer \
		syntax/syntax_make_connect \
		syntax/syntax_make_redir \
		syntax/syntax_make_simplecmd \
		syntax/syntax_make_subshell \
		syntax/syntax_make_word \
		syntax/syntax_parser \
		syntax/syntax_print \
		syntax/syntax

SRCS_FULL = $(addsuffix .c, $(addprefix $(ROOT_PATH)/srcs/, $(SRCS)))
OBJ = $(SRCS_FULL:.c=.o)

# Libft path
LIBFT_ROOT = $(ROOT_PATH)/libft

INC = -I$(ROOT_PATH)/includes -I$(LIBFT_ROOT)
LIB = -L/usr/lib -L$(LIBFT_ROOT) -lreadline -ltermcap -lft
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
