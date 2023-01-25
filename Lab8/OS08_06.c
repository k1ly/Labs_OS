#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main()
{
	int i = 0;
	clock_t t1 = clock();
	while(1)
	{
		i++;
		double t2 = (double)(clock() - t1) / CLOCKS_PER_SEC;
		if (t2 == 2.0) {
			printf("%d: %d\n", (int)t2, i);
			printf("Time passed - %f\n", t2);
			break;
		}
	}
	exit(0);
}