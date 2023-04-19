#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <locale.h>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	int param;
	if(argc > 1)
		param = atoi(argv[1]);
	else
	{
		printf("Параметр 1 должен быть определен - целое число\n");
		exit(1);
	}
	int in = open("./os09_05.txt", O_RDONLY);
	int out = open(param % 2 != 0 ? "./OS09_06_1.txt" : "./OS09_06_2.txt", O_CREAT|O_WRONLY);
	int rowCount = 1;
	char c;
	while(read(in, &c, 1) == 1)
	{
		if((param % 2 != 0 && rowCount % 2 != 0) || (param % 2 == 0 && rowCount % 2 == 0))
		{
			write(out, &c, 1);
		}
		if(c == '\n')
			rowCount++;
	}
	printf("Успех!\n");
	exit(0);
}