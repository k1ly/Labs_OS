#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "ru");
	int in = open("./os09_05.txt", O_RDONLY);
	int rowCount = 1;
	char c;
	while(read(in, &c, 1) == 1)
	{
		if(c == '\n')
			rowCount++;
	}
	printf("Строк в файле: %d\n", rowCount);
	exit(0);
}