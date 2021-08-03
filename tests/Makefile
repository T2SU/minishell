CC = clang
CFLAGS = -Wall -Wextra -Werror -g

INC = -I../includes -I.
LIBSRCS = $(wildcard ../srcs/container/*.c) \
			$(wildcard ../srcs/libft/*.c)

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
