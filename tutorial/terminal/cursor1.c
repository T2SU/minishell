#include <termios.h>
#include <termcap.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MOVE_UP "\033[A"
#define MOVE_DOWN "\033[B"
#define MOVE_RIGHT "\033[C"
#define MOVE_LEFT "\033[D"
#define BACKSPACE "\x7f"

static int get_cursor_pos(int *row, int *col)
{
	char buf[256];
	write(STDOUT_FILENO, "\033[6n", 4);
	int ret = read(STDIN_FILENO, buf, sizeof(buf) - 1);
	if (ret <= 0)
		return 0;
	buf[ret] = '\0';
	if (buf[0] != '\033' || buf[1] != '[')
		return 0;
	*row = 0;
	*col = 0;
	char *str = &buf[2];
	while (*str && *str != ';')
		*row = (*row * 10) + (*(str++) - '0');
	if (*(str++) == '\0')
		return 0;
	while (*str && *str != 'R')
		*col = (*col * 10) + (*(str++) - '0');
	*col = *col - 1;
	*row = *row - 1;
	return 1;
}

static int ft_putchar(int c)
{
	write(STDOUT_FILENO, &c, 1);
	return 0;
}

int main(void)
{
	struct termios term;
	char buf[256];
	int r;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;    // non-canonical input 설정
	term.c_lflag &= ~ECHO;      // 입력 시 터미널에 보이지 않게
	term.c_cc[VMIN] = 1;        // 최소 입력 버퍼 크기
	term.c_cc[VTIME] = 0;       //버퍼 비우는 시간 (timeout)
	tcsetattr(STDIN_FILENO, TCSANOW, &term);


	tgetent(NULL, "xterm");
	char *cm = tgetstr("cm", NULL); // cursor motion
	char *ce = tgetstr("ce", NULL); // clear line from cursor

	int row, col;
	while ((r = read(0, buf, sizeof(buf) - 1)) > 0)
	{
		buf[r] = '\0';
		get_cursor_pos(&row, &col);
		if (!strcmp(buf, MOVE_UP))
		{
			if (row > 0)
				tputs(tgoto(cm, col, --row), 1, &ft_putchar);
		}
		else if (!strcmp(buf, MOVE_DOWN))
		{
			tputs(tgoto(cm, col, ++row), 1, &ft_putchar);
		}
		else if (!strcmp(buf, MOVE_LEFT))
		{
			if (col > 0)
				tputs(tgoto(cm, --col, row), 1, &ft_putchar);
		}
		else if (!strcmp(buf, MOVE_RIGHT))
		{
			tputs(tgoto(cm, ++col, row), 1, &ft_putchar);
		}
		else if (!strcmp(buf, BACKSPACE))
		{
			if (col > 0)
				col--;
			tputs(tgoto(cm, col, row), 1, ft_putchar);
			tputs(ce, 1, ft_putchar);
		}
		else
		{
			int i = 0;
			while (buf[i])
			{
				ft_putchar(buf[i]);
				i++;
				col++;
			}
		}
	}
	return 0;
}
