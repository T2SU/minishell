#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int fd[2];
	pid_t pid;

	if (pipe(fd) == -1)
		return 1;
	if ((pid = fork()) > 0)
	{
		close(fd[1]);
		/* Read from child through piped fd */
		char buf[32];
		int r;
		while ((r = read(fd[0], buf, sizeof(buf))) > 0)
			write(1, buf, r);
		/* ******************************** */
	}
	else
	{
		// 이 시점에서 STDOUT_FILENO = tty (터미널)
		printf("child STDOUT isatty=%d\n", isatty(STDOUT_FILENO));
		dup2(fd[1], STDOUT_FILENO);
		dup2(fd[1], STDERR_FILENO);
		// 이 시점에서 STDOUT_FILENO != tty (터미널이 아님)
		printf("child STDOUT isatty=%d\n", isatty(STDOUT_FILENO));
	}
	return 0;
}
