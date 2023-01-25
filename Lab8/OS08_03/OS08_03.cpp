#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	int i = 0;
	clock_t t1 = clock();
	while (true)
	{
		i++;
		double t2 = (double)(clock() - t1) / CLK_TCK;
		if (t2 == 15.0) {
			cout << t2 << ": " << i << endl;
			break;
		}
		if (t2 - (int)t2 == 0 && (int)t2 % 3 == 0)
			cout << t2 << ": " << i << endl;
	}
	system("pause");
}