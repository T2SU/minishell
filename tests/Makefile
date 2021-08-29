# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/15 16:22:38 by smun              #+#    #+#              #
#    Updated: 2021/08/29 15:44:23 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
#-fsanitize=address

INC = -I../includes -I. -I../libft
LIBSRCS = \
			../srcs/variable.c \
			../srcs/safe_memory.c \
			$(wildcard ../srcs/command/*.c) \
			$(wildcard ../srcs/context/*.c) \
			$(wildcard ../srcs/execution/*.c) \
			$(wildcard ../srcs/module/*.c) \
			$(wildcard ../srcs/shell/*.c) \
			$(wildcard ../srcs/stack/*.c) \
			$(wildcard ../srcs/strbuf/*.c) \
			$(wildcard ../srcs/syntax/*.c)
LIBOBJ = $(LIBSRCS:.c=.o)

LIBFTPATH = ../libft
LIB = -L$(LIBFTPATH) -lft -ltermcap -lreadline

# macOS 에서는, 프로젝트에 동봉된 라이브러리로 컴파일
ifeq ($(shell uname -s), Darwin)
	INC += -I../readline/include
	LIB += -L../readline/lib

#	Apple silicon 칩셋에서는 Rosetta 2로 구동될 수 있게끔 x86_64로 크로스 컴파일
	ifeq ($(shell uname -m), arm64)
		CFLAGS += -target x86_64-darwin-macho
	endif
endif

TESTSRCS = $(wildcard test_*.c)
TESTOBJ = $(TESTSRCS:.c=.o)
TESTLIBSRCS = testlib.c
TESTLIBOBJ = $(TESTLIBSRCS:.c=.o)

all : $(LIBOBJ) $(TESTOBJ) $(TESTLIBOBJ)
	@$(MAKE) -C $(LIBFTPATH) bonus
	@for file in $(TESTOBJ) ; do \
		echo Building $${file%%.*} ; \
		$(CC) $(CFLAGS) -o $${file%%.*}.out $(LIBOBJ) $(TESTLIBOBJ) $(LIB) $${file%%.*}.o ; \
	done

run : all
	@for file in $(TESTOBJ) ; do \
		./$${file%%.*}.out ; \
	done

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	$(MAKE) -C $(LIBFTPATH) $@
	rm -rf $(LIBOBJ) $(TESTOBJ) $(TESTLIBOBJ)

fclean : clean
	$(MAKE) -C $(LIBFTPATH) $@
	rm -rf *.out

re : clean all

.PHONY: all run clean fclean re
