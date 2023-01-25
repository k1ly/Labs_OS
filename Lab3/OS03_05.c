#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void cycle(int k, char* s)
{
	for (int i = 0; i < k; i++)
	{
		sleep(1);
		printf("%s: %d\n", s, i);
	}
}

int main()
{
	pid_t pid;
	switch(pid = fork())
	{
		case -1: perror("Fork error");
			exit(-1);
		case 0: cycle(100, "OS03_05_1");
			exit(0);
		default: cycle(100, "OS03_05");
			wait(NULL);
	}
	exit(0);
}

// ps -ef
// ls -l /proc | grep kirill