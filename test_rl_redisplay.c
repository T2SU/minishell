#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main(void)
{
	signal(SIGINT, &handler);
	while (1)
	{
		char *str = readline("$> ");
		printf("%s\n", str);
		free(str);
	}
	return 0;
}
