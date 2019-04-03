/*
File : EqParser.h 
Description : This header file contains functions and constants for parsing math equations
Implementation file: EqParser.c
*/
#include <math.h>
#ifndef _EQ_PARSER_H_
#pragma once
#define _EQ_PARSER_H_
#define ISALNUM(x) (((0x30 <= (x)) & ((x) <= 0x39))\
					|((0x41 <= (x)) & ((x) <= 0x5A))\
					|((0x61 <= (x)) & ((x) <= 0x7A)))

#define ISNUM(x) ((0x30 <= (x)) & ((x) <= 0x39))

#define ISALPHA(x) (((0x41 <= (x)) & ((x) <= 0x5A))\
					|((0x61 <= (x)) & ((x) <= 0x7A)))
/* abs function for int */
#define NABS(x) ((~(x) + 1) * ((x) < 0) + (x) * ((x) >= 0))/* if x < 0 abs it else return as it was */

#define ISCLOSER (point, x, y) NABS((point) - (x)) < NABS((point) - (y))/* return true if x closer to the point than y */
typedef enum
{
	NUM,/* number */
	OPR,/* math operator */
	VAR /* variable */
}ObjectType;
#ifdef INTV
typedef struct
{
	union
	{
		char sym;/* contains either math sign or var */
		int num;/* contains number, also all assignments passing through this var */
	};
}Object;
#endif
typedef struct
{
	union
	{
		char sym;/* contains either math sign or var */
		float num;/* contains number, also all assignments passing through this var */
	};
}Object;

typedef struct Node
{
	ObjectType type;/* contains type of the object */
	Object object;/* containst value */
	struct Node* head;/* previous node */
	struct Node* left;/* child left node */
	struct Node* right;/* child right node*/
}Node;

/* the fuction checks is all parentheses complete */
int CheckParentheses(const char* str, int size);
/* the function below finds a center of an equation */
int FindCenter(const char* eq, int size);
/* the function response for creating new nodes */
#ifdef INTV
Node* CreateNode(Node* parent, ObjectType type, int object);
#endif
Node* CreateNode(Node* parent, ObjectType type, float object);
int isNumber(const char* str, int size);
#ifdef INTV
/* string to int */
int sti(const char* str, int size);
#endif
/* string to float */
float stf(const char* str, int size);
/* the function below returns parsed equation in binary tree format */
Node* ParseEq(Node* head, const char* eq, int size);
void DestroyNode(Node* root);
#endif