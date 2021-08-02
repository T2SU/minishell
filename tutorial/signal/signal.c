#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void on_interrupt(int val)
{
	if (val == SIGINT)
	{
		printf("interrupted!!\n");
		exit(0);
	}
}

int main(void)
{
	signal(SIGINT, &on_interrupt);
	while(1)
		usleep(10000);
	return 0;
}
