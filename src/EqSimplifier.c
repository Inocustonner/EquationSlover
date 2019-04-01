#include "../headers/EqSimplifier.h"
float pow(float num, float power)
{
	float res = 1;
	while (power)
	{
		res*=num;
		--power;
	}
	return res;
}

Result GetResult(Node* node)
{
	Result ret;
	if (OPR == node->type)
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
			ret.num = pow(left.num, right.num);
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
	else if (VAR == node->type)
	{
		ret.isVar = 1;
		ret.num = 1.f;
		return ret;
	}
	ret.num = node->object.num;
	ret.isVar = 0;
	return ret;
}
