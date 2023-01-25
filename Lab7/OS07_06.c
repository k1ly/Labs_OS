#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void child_thread(char* name)
{
	for(int i = 0; i < 90; i++)
	{
		if(i == 30)
			pthread_mutex_lock(&mutex);
		if(i == 60) {
			pthread_mutex_unlock(&mutex);
			sleep(0.1);
			pthread_mutex_lock(&mutex);
			pthread_mutex_unlock(&mutex);
		}
		sleep(0.1);
		printf("%s - %d\n", name, i);

	}
	pthread_exit("Child thread");
}

void* child1(void* arg)
{
	child_thread("Child thread 1");
}

void* child2(void* arg)
{
	child_thread("Child thread 2");
}

int main()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_t th1, th2;
	void *r_th1, *r_th2;
	int r1 = pthread_create(&th1, NULL, child1, NULL);
	int r2 = pthread_create(&th2, NULL, child2, NULL);
	pid_t pid = getpid();
	for(int i = 0; i < 90; i++)
	{
		if(i == 30)
			pthread_mutex_lock(&mutex);
		if(i == 60) {
			pthread_mutex_unlock(&mutex);
			sleep(0.1);
			pthread_mutex_lock(&mutex);
			pthread_mutex_unlock(&mutex);
		}
		sleep(0.1);
		printf("%d (Main) - %d\n", pid, i);

	}
	int s1 = pthread_join(th1, (void**)&r_th1);
	int s2 = pthread_join(th2, (void**)&r_th2);
	pthread_mutex_destroy(&mutex);
	exit(0);
}

// gcc -pthread ./os07_06.c -o os07_06
// gcc -D REENTRANT os04_07.c -o os04_07 -lpthread