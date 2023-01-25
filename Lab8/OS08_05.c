#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main()
{
	time_t t1;
	t1 = time(&t1);
	struct tm *tm1;
	tm1 = localtime(&t1);
	printf("Time:\n%d.%d.%d %d:%d:%d\n", tm1->tm_mday, (tm1->tm_mon + 1), (tm1->tm_year + 1900), tm1->tm_hour, tm1->tm_min, tm1->tm_sec);
	exit(0);
}