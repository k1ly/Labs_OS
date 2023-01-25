#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	printf("Starting main process\n");
	system("/mnt/c/Users/Kirill/Documents/Labs/OS/Lab3/OS03_05_1\n");
	pid_t pid = getpid();
	for (int i = 0; i < 100; i++)
	{
		sleep(1);
		printf("%d: %d\n", pid, i);
	}
	exit(0);
}