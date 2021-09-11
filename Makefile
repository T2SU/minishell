# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkim <hkim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/29 17:45:46 by hkim              #+#    #+#              #
#    Updated: 2021/09/11 23:42:01 by hkim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Debug Compilation Flags
# 나중에 제출 등에서는 아래 조건의 코멘트를 해제하여 기본적으로는 디버깅용 CFLAGS가 추가되지 않도록 해야함.
# ifeq ($(DEBUG),1)
	CFLAGS += -g -fsanitize=address
# endif
ifeq ($(VERBOSE),1)
	CFLAGS += -DVERBOSE=1
endif


ROOT_PATH = .
SRCS = \
		main \
		variable \
		safe_memory \
		array \
		wildcard \
		wildcard2 \
		sort \
		word \
		argument \
		context/context \
		context/context_wait \
		context/context_error \
		context/context_error2 \
		context/context_delivery_signal \
		context/ft_basename \
		context/ft_random \
		context/ft_strsignal \
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

# macOS 에서는 brew로 설치된 readline 경로를 찾아와서 라이브러리를 로드하도록 변경.
ifeq ($(shell uname -s), Darwin)
	READLINE_ROOT = $(shell brew --prefix readline)
	INC += -I$(READLINE_ROOT)/include
	LIB += -L$(READLINE_ROOT)/lib

#	Apple silicon 칩셋에서는 Rosetta 2로 구동될 수 있게끔 x86_64로 크로스 컴파일
	ifeq ($(shell uname -m), arm64)
		CFLAGS += -target x86_64-darwin-macho
	endif
endif

# Linux 에서, _GNU_SOURCE 매크로 활성화
ifeq ($(shell uname -s), Linux)
	CFLAGS += -D_GNU_SOURCE
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

rmobj:
	find . -name "*.o" | xargs -I{} rm {}

.PHONY: all clean re fclean
