#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int iam;

void on_signal(int sig)
{
	printf("[%02d] signal %d received!\n", iam, sig);
	exit(0);
}

int main(int ac, char *av[])
{
	if (ac < 2)
	{
		printf("no argument\n");
		return 1;
	}
	iam = atoi(av[1]);
	signal(SIGINT, &on_signal);
	while(1)
		sleep(-1);
	return 0;
}
