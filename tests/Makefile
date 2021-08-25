# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/15 16:22:38 by smun              #+#    #+#              #
#    Updated: 2021/08/25 15:34:12 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
#-fsanitize=address

INC = -I../includes -I. -I../libft
LIBSRCS = \
			../srcs/variable.c \
			../srcs/safe_memory.c \
			$(wildcard ../srcs/stack/*.c) \
			$(wildcard ../srcs/strbuf/*.c) \
			$(wildcard ../srcs/shell/*.c) \
			$(wildcard ../srcs/context/*.c) \
			$(wildcard ../srcs/execution/*.c) \
			$(wildcard ../srcs/syntax/*.c)
LIBOBJ = $(LIBSRCS:.c=.o)

LIBFTPATH = ../libft
LIB = -L$(LIBFTPATH) -L/usr/lib -lft -ltermcap -lreadline

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
