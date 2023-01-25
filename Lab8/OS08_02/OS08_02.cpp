#include <iostream>

using namespace std;

int main()
{
	int i = 0;
	clock_t t1 = clock();
	while (true)
	{
		i++;
		double t2 = (double)(clock() - t1) / CLK_TCK;
		if (t2 == 5.0 || t2 == 10.0)
			cout << t2 << ": " << i << endl;
		if (t2 == 15.0) {
			cout << t2 << ": " << i << endl;
			break;
		}
	}
	system("pause");
}