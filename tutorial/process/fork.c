#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	int fd[] = {-1, -1};
	if (pipe(fd) == -1)
		return 1;
	int pid = fork();
	if (pid)
	{
		dup2(fd[1], STDOUT_FILENO);
		dup2(fd[1], STDERR_FILENO);
		char *av[] = {"/bin/ls", "-l", "/Users/tsy", NULL};
		execve("/bin/ls", av, envp);
	}
	else
	{
		close(fd[1]);
		char buf[32];
		int r;
		while ((r = read(fd[0], buf, sizeof(buf))) > 0)
			write(1, buf, r);
	}
	return 0;
}
