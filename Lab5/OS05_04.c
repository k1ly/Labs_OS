#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sched.h>


int main()
{
	pid_t pid = getpid();
	pid_t tid = getgid();
	int nice = getpriority(PRIO_PROCESS, 0);
	printf("PID = %d\n", pid);
	printf("TID = %d\n", tid);
	printf("priority (nice) = %d\n", nice);
	cpu_set_t set;
	CPU_ZERO(&set);
	if (sched_getaffinity(0, sizeof(cpu_set_t), &set) == 0) {
		int is = 0;
		for (int i = 0; i < CPU_SETSIZE; i++)
		{
			is = CPU_ISSET(i, &set);
			if (is)
				printf("cpu %d is %s\n", i, is ? "set" : "unset");
		}
	}
	else
		printf("sched_getaffinity = ERROR");
	exit(0);
}