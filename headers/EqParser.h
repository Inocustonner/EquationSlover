/*
File : EqParser.h 
This header file contains functions and constants for parsing math equations 
Implementation file: EqParser.c
*/
#ifndef _EQ_PARSER_H_
#pragma once
#define _EQ_PARSER_H_
#define ISALNUM(x) (((0x30 <= (x)) & ((x) <= 0x39))\
					|((0x41 <= (x)) & ((x) <= 0x5A))\
					|((0x61 <= (x)) & ((x) <= 0x7A)))

#define ISNUM(x) ((0x30 <= (x)) & ((x) <= 0x39))

#define ISALPHA(x) (((0x41 <= (x)) & ((x) <= 0x5A))\
					|((0x61 <= (x)) & ((x) <= 0x7A)))

typedef enum
{
	NUM,/* number */
	OPR,/* math operator */
	VAR /* variable */
}ObjectType;

typedef struct
{
	union
	{
		char sym;/* contains either math sign or var */
		int num;/* contains number, also all assignments passing through this var */
	};
}Object;

typedef struct Node
{
	struct Node* head;/* previous node */
	struct Node* left;/* child left node */
	struct Node* right;/* child right node*/
	ObjectType type;/* contains type of the object */
	Object object;/* containst value */
}Node;

/* abs for int */
inline int nabs(int x);
/* the fuction checks is all parentheses complete */
int CheckParentheses(const char* str, int size);
/* the function below finds a center of an equation */
int FindCenter(const char* eq, int size);
/* the function response for creating new nodes */
Node* CreateNode(Node* parent, ObjectType type, int object);
int isNumber(const char* str, int size);
/* string to int */
int sti(const char* str, int size);
/* the function below returns parsed equation in binary tree format */
Node* ParseEq(Node* head, const char* eq, int size);
void DestroyNode(Node* root);
#endif