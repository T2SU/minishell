#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	char	*env;

	while (1)
	{
		env = *(envp++);
		if (env == NULL)
			break ;
		write(1, env, strlen(env));
		write(1, "\n", 1);
	}
	return 0;
}
