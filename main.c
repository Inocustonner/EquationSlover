#include <stdio.h>
#include "headers/EqParser.h"
int main(int argc, char* argv[])
{
	char eq[] = "3*(2+4)/2";
	Node* root = ParseEq(NULL, eq, strlen(eq));
	DestroyNode(root);
#if defined(_MSC_VER) || defined(_WIN32)
	system("pause");
#endif	
	return 0;
}