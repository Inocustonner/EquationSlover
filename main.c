#include <stdio.h>
#include "headers/EqSimplifier.h"
int main(int argc, char* argv[])
{
	char eq[] = "5+5";
	printf("%f", SloveEq(eq, strlen(eq)));
#if defined(_MSC_VER) | defined(_WIN32)
	system("pause");
#endif	
	return 0;
}