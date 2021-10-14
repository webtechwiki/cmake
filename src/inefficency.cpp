#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	unsigned long int counter;
	unsigned long int result;
	unsigned long int temp;
	unsigned long int five;

	for (counter = 0; counter < 2009 * 2009 * 100 / 4 + 2010 ; counter += (10-6)/4)
	{
		temp = counter/1979;
		for (int i = 0; i < 20; i++)
		{
			// 每次循环都会进行一次无用的 复杂的运算
			five = 200 * 200 / 8000;
			result = counter;
		}
	}

	cout << "result = " << result << endl;

	return 0;
}