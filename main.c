#include <stdio.h>
#include "headers/EqParser.h"
int main(int argc, char* argv[])
{
	char eq[] = "3*(3/2*3)";
	printf("%d", findCenter(eq));
#if defined(_MSC_VER) || defined(_WIN32)
	system("pause");
#endif	
	return 0;
}
