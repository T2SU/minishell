CC = clang
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

INC = -I../includes -I../lib/includes -I.
LIBSRCS = $(wildcard ../lib/srcs/list/*.c) \
			$(wildcard ../lib/srcs/libft/memory/*.c) \
			$(wildcard ../lib/srcs/libft/string/*.c) \
			$(wildcard ../lib/srcs/error/*.c) \
			$(wildcard ../srcs/*.c) \
			$(wildcard ../srcs/lex/*.c)

LIBOBJ = $(LIBSRCS:.c=.o)
TESTSRCS = $(wildcard test_*.c)
TESTOBJ = $(TESTSRCS:.c=.o)
TESTLIBSRCS = testlib.c
TESTLIBOBJ = $(TESTLIBSRCS:.c=.o)

all : compile
	@for file in $(TESTOBJ) ; do \
		./$${file%%.*}.out ; \
	done

compile : $(LIBOBJ) $(TESTOBJ) $(TESTLIBOBJ)
	@for file in $(TESTOBJ) ; do \
		$(CC) $(CFLAGS) -o $${file%%.*}.out $(LIBOBJ) $(TESTLIBOBJ) $${file%%.*}.o ; \
	done

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	rm -rf $(LIBOBJ) $(TESTOBJ) $(TESTLIBOBJ)

fclean : clean
	rm -rf *.out
