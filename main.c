#include <stdio.h>
#include "headers/EqSimplifier.h"
int main(int argc, char* argv[])
{
	
	char eq[] = "(1440/900)*10";
	Node* root = ParseEq(NULL, eq, strlen(eq));
	printf("result : %f\n", GetResult(root).num);
	DestroyNode(root);
#if defined(_MSC_VER) || defined(_WIN32)
	system("pause");
#endif	
	return 0;
}