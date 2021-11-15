#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	int N = 100;
	int sum = 0;
	int i = 1;

	while(i <= N){
		sum = sum + i;
		i = i + 1;
	}

	cout << "sum = " << sum <<endl;
	cout << "The program is over " <<endl;

	return 0;
}
