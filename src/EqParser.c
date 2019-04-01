#include "../headers/EqParser.h"
#include <stdio.h>
inline int nabs(int x)
{
	return (~x + 1) * (x < 0) + x * (x >= 0);/* if x < 0 abs it else return as it was */
}

void print(const char* str, int size)
{
	for (int i = 0; i < size; ++i)
		printf("%c", str[i]);
}


int CheckParentheses(const char* str, int size)
{
	char bool = 0;
	int i = 1;
	while (i < size)
	{
		bool += (str[i - 1] == '(');
		bool -= (str[i++] == ')');
	}
	return bool == 0;
}

int FindCenter(const char* eq, int size)
{
	size = (size) * (size != 0) + strlen(eq) * (size == 0);
	char prior = 2;/* prior 0 for '+' and '-' 1 for '*' and '/' 2 for '^' */
	char inParenthese = 0;
	int result = -1;
	int center = size / 2;
	int i = 1;
	/* parentheses check:
	if whole equation placed in parentheses then skip them */
	if (('(' == eq[i - 1]) & (')' == eq[size - 1]))
	{
		if (CheckParentheses(eq + 1, size - 2))
		{
			inParenthese = -1;
			size -= 1;
		}
	}
	for (; i < size; ++i)
	{
		while (inParenthese += (eq[i - 1] == '('))/* if we're in parentheses than skip it but only if eq not starts with them */
		{
			inParenthese -= (eq[i++] == ')');
		}
		if ((eq[i] == '+') | (eq[i] == '-'))
		{
			if ((eq[i] == '-') & (ISALNUM(eq[i - 1])^1))/* if '-' is before a number and before '-' not a number of var*/
			{
				continue;
			}
			if ((nabs(center - result) > nabs(center - i)) | (prior ^0))/* if i closer to the center than previous result or previous result was either '*' or '/' or '^'  or nothing */
			{
				result = i;
			}
			prior = 0;
		}
		if (prior)/* if prior != 0 */
		{
			if ((eq[i] == '*') | (eq[i] == '/'))
			{
				if ((nabs(center - result) > nabs(center - i)))/* if i closer to the center than previous result or previous result was '^' or nothing*/
				{
					result = i;
				}
				prior = 1;
			}
			if ((eq[i] == '^') & (prior - 1))
			{
				if ((nabs(center - result) > nabs(center - i)))/* if i closer to the center than previous result or previous result was '^' or nothing*/
				{
					result = i;
				}
			}
		}
	}
	return result;
}

Node* CreateNode(Node* parent, ObjectType type, int object)
{
	Node* newnode = malloc(sizeof(Node));
	newnode->head = parent;
	newnode->type = type;
	newnode->object.num = object;
	newnode->left = (void*)0;
	newnode->right = (void*)0;
	return newnode;
}

int isNumber(const char* str, int size)
{
	int i = 0;
	if ('-' == str[0]) ++i;
	for (; i < size; ++i)
	{
		if (ISNUM(str[i]) ^ 1)/* if (!ISNUM(str[i])) */
		{
			return 0;
		}
	}
	return 1;
}

int sti(const char* str, int size)
{
	int ret = 0;
	int i = size - 1;
	int pos = 1;
	for (; i >= 0; --i)
	{
		ret += pos * (int)(str[i] - 0x30) * (ISNUM(str[i]));
		pos *= 10;
	}
	ret -= ret * 2 * ('-' == str[i + 1]);
	return ret;
}

inline Node* CreateNodeFromVal(const char* str, int size)
{
	if (isNumber(str, size))
	{
		return CreateNode((void*)0, NUM, sti(str, size));
	}
	if (ISALPHA(str, size))
	{
		return CreateNode((void*)0, VAR, *str);
	}
	return CreateNode((void*)0, OPR, '?');
}

Node* ParseEq(Node* head, const char* eq, int size)
{
	print(eq, size);
	printf("\n");
	int divisor = FindCenter(eq, size);
	if (-1 == divisor)
	{
		return CreateNodeFromVal(eq, size);
	}
	printf(" divisor : %c\n", eq[divisor]);
	Node* node = CreateNode(head, OPR, eq[divisor]);
	node->left = ParseEq(node, eq, divisor);
	node->right = ParseEq(node, eq + divisor + 1, size - divisor - 1);
	return node;
}

void DestroyNode(Node* root)
{
	if (root->left)
		DestroyNode(root->left);
	if (root->right)
		DestroyNode(root->right);
	printf("%c ", root->object.sym);
	printf("%d\n", root->object.sym);
	free(root);
}