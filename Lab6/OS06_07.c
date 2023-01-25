#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid = getpid();
	int size = 256 * 1024 * 1024;
	int* x = malloc(size);
	printf("malloc(256 MB) = %p\n", x);
	for(int i = 0; i < size/sizeof(int); i++)
	{
		x[i] = i;
	}
	sleep(60 * 60);
	free(x);
	exit(0);
}