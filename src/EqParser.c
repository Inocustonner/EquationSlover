#include "../headers/EqParser.h"
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

inline char IsCloser(int point, int x, int y)
{
	return NABS(point - x) < NABS(point - y);
}

int FindCenter(const char* eq, int size)
{
	size = (size) * (size != 0) + strlen(eq) * (size == 0);
	char prior = 2;/* prior 0 for '+' and '-' 1 for '*' and '/' 2 for '^' */
	char inParenthese = 0;
	int result = -1;
	int center = size;
	int i = 1;
	for (; i < size; ++i)
	{
		if (inParenthese += (eq[i - 1] == '('))/* if we're in parentheses than skip it but only if eq not starts with them */
		{
			inParenthese -= (eq[i] == ')');
			continue;
		}
		if ((eq[i] == '+') | (eq[i] == '-'))
		{
			if (('-' == eq[i]) & (ISALNUM(eq[i - 1])^1) & (eq[i - 1] ^ ')'))/* if '-' is before a number and before '-' not a number neither var nor ')' */
			{
				continue;
			}
			if ((IsCloser(center, i, result)) | (prior ^ 0))/* if i closer to the center than previous result or previous result was either '*' or '/' or '^'  or nothing */
			{
				result = i;
			}
			prior = 0;
		}
		if (prior)/* if prior != 0 */
		{
			if ((eq[i] == '*') | (eq[i] == '/'))
			{
				if ((IsCloser(center, i, result)))/* if i closer to the center than previous result or previous result was '^' or nothing*/
				{
					result = i;
				}
				prior = 1;
			}
			if ((eq[i] == '^') & (prior - 1))
			{
				if ((IsCloser(center, i, result)))/* if i closer to the center than previous result or previous result was '^' or nothing*/
				{
					result = i;
				}
			}
		}
	}
	return result;
}
#ifdef INTV
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
#endif
Node* CreateNode(Node* parent, ObjectType type, ...)
{
	Node* newnode = malloc(sizeof(Node));
	newnode->head = parent;
	newnode->type = type;
	newnode->left = (void*)0;
	newnode->right = (void*)0;
	va_list ap;
	__crt_va_start(ap, type);
	switch (type)
	{
	case VAR:
	case OPR:
		{
			newnode->object.sym = __crt_va_arg(ap, char);
			break;
		}
	case FNC:
	case NUM:
		{
			newnode->object.num = __crt_va_arg(ap, double);
			break;
		}
	}
	__crt_va_end(ap);
	return newnode;
}
void print(const char * str, int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%c", str[i]);
	}
}

Node* CreateNodeFromFunction(Node* head, const char* eq, const int size, const int pos)
{
	Node* newnode = CreateNode(head, FNC, (float)pos);
	newnode->right = ParseEq(newnode, eq + strlen(functions[pos]), size - strlen(functions[pos]));
	return newnode;
}

inline Node* CreateNodeFromVal(const char* str, int size)
{
	if (isNumber(str, size))
	{
		return CreateNode((void*)0, NUM, stf(str, size));
	}
	if (ISALPHA(str, size))
	{
		return CreateNode((void*)0, VAR, *str);
	}
	return CreateNode((void*)0, OPR, '?');
}

int isNumber(const char* str, int size)
{
	int i = 0;
	if ('-' == str[0]) ++i;
	for (; i < size; ++i)
	{
		if ((ISNUM(str[i]) ^ 1) & (str[i] != '.'))/* if (!ISNUM(str[i])) and str[i] != '.' if number is float */
		{
			return 0;
		}
	}
	return 1;
}

#ifdef INTV
int sti(const char* str, int size)
{
	int ret = 0;
	int i = size - 1;
	int pos = 1;
	for (; i >= ('-' == str[0]); --i)/* if number less than zero don't process minuse here */
	{
		ret += pos * (int)(str[i] - 0x30);
		pos *= 10;
	}
	ret -= ret * 2 * ('-' == str[0]);
	return ret;
}

float stf(const char* str, int size)
{
	float res = 0;/* var that contain the result */
	float exp = 1;
	int i;
	int d = 0;
	for (i = size - 1; i >= ('-' == str[0]); --i)
	{
		res += exp * (str[i] - 0x30) * ('.' != str[i]);
		exp *= 10.f * ('.' != str[i]) + ('.' == str[i]);
		d += ('.' == str[i])*i;
	}
	res /= powf(10.f, (size - 1 - d)*(d != 0));
	res -= 2.f * res * ('-' == str[0]);
	return res;
}
#endif
float stf(const char* str, int size)
{
	float res;
	res = 0;
	int i;
	int d = 0;
	for (i = size - 1; i >= ('-' == str[0]); --i)
	{
		res += powf(10.f, size - i - 1 - (d != 0)) * (str[i] - 0x30) * ('.' != str[i]);
		d += ('.' == str[i])*i;
	}
	res /= powf(10.f, (size - d - 1) * (d != 0));
	res -= 2.f * res * ('-' == str[0]);
	return res;
}

int MatchFunction(const char* eq, int size)
{
	int i = 0;
	int j;
	bool done;
	do
	{
		done = 1;
		for (j = 0; (j < size) & (j < strlen(functions[i])); ++j)
		{
			if (eq[j] != functions[i][j])
			{
				done = 0;
				break;
			}
		}
		++i;
	} while ((i < FUNCTIONS_ARRAY_SZ) & (~done & 0b1));
	return i * done;
}

Node* ParseEq(Node* head, const char* eq, int size)
{
	/* parentheses check:
	if whole equation placed in parentheses then skip them */
	if (('(' == eq[0]) & (')' == eq[size - 1]))
	{
		if (CheckParentheses(eq + 1, size - 2))
		{
			eq += 1;
			size -= 2;
		}
	}
	int divisor = FindCenter(eq, size);
	if (-1 == divisor)
	{
		/* just using 1 var to avoid cache pollution */
		if (divisor = MatchFunction(eq, strlen(eq)))
		{
			return CreateNodeFromFunction(head, eq, size, divisor - 1);
		}
		return CreateNodeFromVal(eq, size);
	}
	Node* node = CreateNode(head, OPR, eq[divisor]);
	node->left = ParseEq(node, eq, divisor);
	node->right = ParseEq(node, eq + divisor + 1, size - divisor - 1);
	return node;
}

void DestroyNode(Node* root)
{
	if ((void*)0 == root)
	{
		return;
	}
	if ((void*)0 != root->left)
	{
		DestroyNode(root->left);

	}
	if ((void*)0 != root->right)
	{
		DestroyNode(root->right);
	}
	free(root);
}