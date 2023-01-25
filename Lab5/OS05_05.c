#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
	for (int i = 0; i < 40000000000; i++)
	{
		printf("i = %d\n", i);
	}
	exit(0);
}

// top
// renice -n 100 pid