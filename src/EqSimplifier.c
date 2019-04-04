#include "../headers/EqSimplifier.h"
Result GetResult(Node* node)
{
	Result ret;
	switch(node->type)
	{
	case OPR:
	{
		Result left = GetResult(node->left);
		if (left.isVar)/* for now i have no idea how to deal with vars so i'll just join branches that i can */
		{
			return left;
		}
		Result right = GetResult(node->right);
		if (right.isVar)
		{
			return right;
		}
		switch (node->object.sym)
		{
		case '+':
		{
			ret.num = left.num + right.num;
			break;
		}
		case '-':
		{
			ret.num = left.num - right.num;
			break;
		}
		case '*':
		{
			ret.num = left.num * right.num;
			break;
		}
		case '/':
		{
			ret.num = left.num / right.num;
			break;
		}
		case '^':
		{
			ret.num = powf(left.num, right.num);
			break;
		}
		}
		ret.isVar = 0;
		/*let last root exist free only it's child */
		free(node->left);
		node->left = (void*)0;
		free(node->right);
		node->right = (void*)0;
		return ret;
	}
	case FNC:
	{
		if (1 == (ret = GetResult(node->right)).isVar)
		{
			return ret;
		}
		switch ((int)node->object.num)
		{
		case 0:/* sin */
		{
			ret.num = sinf(ret.num);
			break;
		}
		case 1:/* cos */
		{
			ret.num = cosf(ret.num);
			break;
		}
		case 2:/* tg */
		{
			ret.num = tanf(ret.num);
			break;
		}
		case 3:/* ctg */
		{
			ret.num = 1.f / tanf(ret.num);
			break;
		}
		case 4:/* sqrt */
		{
			ret.num = sqrt(ret.num);
			break;
		}
		}
		ret.isVar = 0;
		free(node->left);
		node->left = (void*)0;
		free(node->right);
		node->right = (void*)0;
		return ret;
	}
	case VAR:
	{
		ret.isVar = 1;
		ret.num = 1.f;
		return ret;
	}
	case NUM:
		ret.num = node->object.num;
		ret.isVar = 0;
		return ret;
	}
}

float SloveEq(char* eq, int size)
{
	Node* root = ParseEq(NULL, eq, size);
	float res = GetResult(root).num;
	DestroyNode(root);
	return res;
}