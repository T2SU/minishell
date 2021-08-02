#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <termcap.h>
#include <unistd.h>

// SIGINT (Ctrl+C) 시그널 보내면, 입력 중이던 내용을 캔슬하고 개행시키고,
// 새로운 프롬포트를 내야 함.

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	set_term(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;      // Ctrl키 조합을 터미널에 표시하지 않음. (^C, ^F 등)
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int main(void)
{
	set_term();
	signal(SIGINT, &handler);
	while (1)
	{
		char *str = readline("$> ");
		printf("%s\n", str);
		free(str);
	}
	return 0;
}
