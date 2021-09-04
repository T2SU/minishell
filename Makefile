# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/29 17:45:46 by hkim              #+#    #+#              #
#    Updated: 2021/09/03 17:58:57 by hkim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Debug Compilation Flags
# 나중에 제출 등에서는 아래 조건의 코멘트를 해제하여 기본적으로는 디버깅용 CFLAGS가 추가되지 않도록 해야함.
# ifeq ($(DEBUG),1)
	CFLAGS += -g -DVERBOSE=1 -fsanitize=address
# endif

ROOT_PATH = .
SRCS = \
		main \
		variable \
		safe_memory \
		array \
		wildcard \
		sort \
		context/context \
		context/context_error \
		context/context_error2 \
		context/ft_basename \
		context/ft_random \
		shell/shell \
		shell/signal \
		shell/stat \
		execution/execution_heredoc \
		execution/execution_heredoc_prepare \
		execution/execution_redirection \
		execution/execution_simplecmd \
		execution/execution_subshell \
		execution/execution_connect \
		execution/execution_install_redir \
		execution/execution \
		command/builtin \
		command/echo \
		command/cd_pwd \
		command/export \
		command/export_utils \
		command/env_unset \
		command/exit \
		command/path \
		dictionary/dict \
		dictionary/dict_make_free \
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
LIB = -L$(LIBFT_ROOT) -lft -lreadline -ltermcap

# macOS 에서는, 프로젝트에 동봉된 라이브러리로 컴파일
ifeq ($(shell uname -s), Darwin)
	INC += -I./readline/include
	LIB += -L./readline/lib

#	Apple silicon 칩셋에서는 Rosetta 2로 구동될 수 있게끔 x86_64로 크로스 컴파일
	ifeq ($(shell uname -m), arm64)
		CFLAGS += -target x86_64-darwin-macho
	endif
endif

NAME = minishell

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJ)
	@make -C $(LIBFT_ROOT) bonus
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	@make -C $(LIBFT_ROOT) clean
	rm -rf $(OBJ)

fclean: clean
	@make -C $(LIBFT_ROOT) fclean
	rm -rf $(NAME)

re: clean all

.PHONY: all clean re fclean
