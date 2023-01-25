#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
	for (int i = 0; i < 1000; i++)
	{
		if (i % 10 == 0)
		{
			sleep(1);
			printf("i = %d\n", i);
			fflush(stdout);
		}
	}
	exit(0);
}

// kill -9 pid