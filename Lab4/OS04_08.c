#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void* child_thread(void* arg)
{
	pid_t pid = getpid();
	for (int i = 0; i < 75; i++) {
		if (i == 50) {
			printf("\nOS04_08_T1 thread is sleeping\n\n");
			sleep(10);
			printf("\nOS04_08_T1 thread is waking up\n\n");
		}
		printf("OS04_08_T1: %d - %d\n", pid, i);
		sleep(1);
	}
	pthread_exit("OS04_08_T1 thread");
}

int main()
{
	pthread_t c_thread;
	void* thread_result;
	int res = pthread_create(&c_thread, NULL, child_thread, NULL);

	pid_t pid = getpid();
	for (int i = 0; i < 100; i++) {
		if (i == 30) {
			printf("\nMain thread is sleeping\n\n");
			sleep(15);
			printf("\nMain thread is waking up\n\n");
		}
		printf("Main: %d - %d\n", pid, i);
		sleep(1);
	}

	int status = pthread_join(c_thread, (void**)&thread_result);
	exit(status);
}

// gcc -D REENTRANT os04_08.c -o os04_08 -lpthread