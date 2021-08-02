#include <sys/stat.h>
#include <stdio.h>

int main(void)
{
	struct stat st;
	const char *path = "./link";

	lstat(path, &st);
	printf("(lstat) %s: %lld bytes\n", path, st.st_size);

	stat(path, &st);
	printf("( stat) %s: %lld bytes\n", path, st.st_size);
	return 0;
}
