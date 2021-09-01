#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>

pthread_mutex_t mutex;

static void ft_putstr(const char *str)
{
	pthread_mutex_lock(&mutex);
	write(1, str, strlen(str));
	pthread_mutex_unlock(&mutex);
}

static void on_signal(int sig, siginfo_t *si, void *uctx)
{
	(void)sig;
	(void)si;
	(void)uctx;
	ft_putstr("on signal!! wait 3 secs\n");
	sleep(3);
	ft_putstr("ok.\n");
}

int main(void)
{
	pid_t child;
	int status;
	struct sigaction sa;

	memset(&mutex, 0, sizeof(pthread_mutex_t));
	memset(&sa, 0, sizeof(struct sigaction));
	child = fork();
	if (child == 0)
	{
		while (1)
			sleep(3);
	}
	else
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = &on_signal;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);

		pthread_mutex_init(&mutex, NULL);
		waitpid(child, &status, 0);
		ft_putstr("waitpid end!\n");
		while (1)
			sleep(1);
		pthread_mutex_destroy(&mutex);
	}
	return (0);
}
