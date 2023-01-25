#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void* child_thread(void* arg)
{
	pid_t pid = getpid();
	for (int i = 0; i < 75; i++) {
		printf("OS04_07_T1: %d - %d\n", pid, i);
		sleep(1);
	}
	pthread_exit("OS04_07_T1 thread");
}

int main()
{
	pthread_t c_thread;
	void* thread_result;
	int res = pthread_create(&c_thread, NULL, child_thread, NULL);

	pid_t pid = getpid();
	for (int i = 0; i < 100; i++) {
		printf("Main: %d - %d\n", pid, i);
		sleep(1);
	}

	int status = pthread_join(c_thread, (void**)&thread_result);
	exit(status);
}

// gcc -D REENTRANT os04_07.c -o os04_07 -lpthread