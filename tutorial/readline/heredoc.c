#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <termcap.h>
#include <unistd.h>
#include <string.h>

// SIGINT (Ctrl+C) 시그널 보내면, 입력 중이던 내용을 캔슬하고 개행시키고,
// 새로운 프롬포트를 내야 함.

int in_heredoc = 0;

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		if (in_heredoc)
			return ;
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

static void read_heredoc()
{
	while (1)
	{
		char *str = readline("> ");
		printf("Typed heredoc:{%s}\n", str);
		if (str && !strcmp(str, "EOF"))
			exit(EXIT_SUCCESS);
		free(str);
	}
}

static void signal_readheredoc(int sig)
{
	(void)sig;
	printf("\n");
	exit(EXIT_FAILURE);
}

static void read_prompt(const char *str)
{
	int status;

	printf("Typed prompt:{%s}\n", str);
	if (str && !strcmp(str, "read"))
	{
		in_heredoc = 1;
		pid_t pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, signal_readheredoc);
			read_heredoc();
		}
		waitpid(pid, &status, 0);
		in_heredoc = 0;
		if (status == 0)
			printf("returned from heredoc\n");
	}
}

int main(void)
{
	set_term();
	signal(SIGINT, &handler);
	while (1)
	{
		char *str = readline("PROMPT$ ");
		read_prompt(str);
		free(str);
	}
	return 0;
}
