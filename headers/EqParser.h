/*
File : EqParser.h 
This header file contains functions and constants for parsing math equations 
Implementation file: EqParser.c
*/
#ifndef _EQ_PARSER_H_
#pragma once
#define _EQ_PARSER_H_
#define ISALNUM(x) (((0x30 <= x) & (x <= 0x39))\
					|((0x41 <= x) & (x <= 0x5A))\
					|((0x61 <= x) & (x <= 0x7A)))

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
	struct Node* left;
	struct Node* right;
	ObjectType type;
	Object object;
}Node;

/* abs for int */
inline int nabs(int x);
/* the function below finds a center of an equation */
int findCenter(char* eq);
/* the function response for creating new nodes */
Node* CreateNode(ObjectType type, int object);
#endif