#include "../headers/EqParser.h"
#include <stdio.h>
inline int nabs(int x)
{
	return (~x + 1) * (x < 0) + x * (x >= 0);/* if x < 0 abs it else return as it was */
}
int findCenter(char* eq)
{
	char prior = 2;/* prior 0 for '+' and '-' 1 for '*' and '/' 2 for '^' */
	char inParenthese = 0;
	int result = -1;
	int center = strlen(eq) / 2;
	int i;
	for (i = 1; i < strlen(eq); ++i)
	{
		while (inParenthese += (eq[i - 1] == '('))/* if we're in parentheses than skip it */
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