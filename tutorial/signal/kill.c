#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void on_signal(int sig)
{
	printf("signal %d received!\n", sig);
	exit(0);
}

int main(void)
{
	int pid = fork();
	if (!pid)
	{
		signal(SIGUSR1, &on_signal);
		while (1)
			usleep(1000000);
	}
	else
	{
		usleep(3000000);
		kill(pid, SIGUSR1);
	}
	return 0;
}
