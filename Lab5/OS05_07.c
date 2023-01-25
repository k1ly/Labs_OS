#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

void cycle(int k, char* s)
{
	int nice = getpriority(PRIO_PROCESS, 0);
	for (int i = 0; i < k; i++)
	{
		sleep(1);
		printf("%s: %d, nice = %d\n", s, i, nice);
	}
}

int main()
{
	pid_t pid;
	switch (pid = fork())
	{
	case -1: perror("Fork error");
		exit(-1);
	case 0:
		nice(-10);
		cycle(100, "Child");
		exit(0);
	default: cycle(100, "Main");
		wait(NULL);
	}
	exit(0);
}

// sudo ./os05_07
// watch ps -u kirill