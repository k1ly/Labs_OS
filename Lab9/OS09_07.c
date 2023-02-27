#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <locale.h>
#include <string.h>
#define BUFFER 100

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	int param1;
	int param2;
	if(argc > 2)
	{
		param1 = atoi(argv[1]);
		param2 = atoi(argv[2]);
		if(param1 < 0 || param2 < 0)
		{
			printf("Параметры 1 и 2 должны быть больше или равны нулю\n");
			exit(2);
		}
	}
	else
	{
		printf("Параметры 1 и 2 должны быть определены - целые числа\n");
		exit(1);
	}
	int in = open("./os09_05.txt", O_RDONLY);
	int out = open("./OS09_07.txt", O_CREAT|O_WRONLY);
	char buf[BUFFER + 1];
	memset(buf, 0, BUFFER + 1);
	int charCount = 0;
	char c;
	int end = lseek(in, -param2, SEEK_END);
	if(end == -1L)
		printf("Error: lseek end\n");
	int set = lseek(in, param1, SEEK_SET);
	if(set == -1L)
		printf("Error: lseek set\n");
	while(read(in, &c, 1) == 1)
	{
		buf[charCount % BUFFER] = c;
		if(set + charCount + 1 == end || strlen(buf) == BUFFER)
		{
			write(out, &buf, strlen(buf));
			memset(buf, 0, BUFFER + 1);
			if(set + charCount + 1 == end)
				break;
		}
		charCount++;
	}
	printf("Всего символов записано: %d\n", charCount + 1);
	exit(0);
}