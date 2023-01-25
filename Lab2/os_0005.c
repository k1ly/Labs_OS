#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid = getpid();
	for (int i = 0; i < 1000; i++)
	{
		printf("%d-%d\n", pid, i);
		sleep(1);
	}
	return 0;
}