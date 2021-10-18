#include <stdio.h>

int main()
{
	#ifdef DEBUG
	  printf("DEBUG LOG\n");
	#endif
	  printf("in\n");
	return 0;
}