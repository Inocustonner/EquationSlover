/*
File : EqSimplifier.h
Description : This header file contains functions and constants for processing and simlifying given equations.
NOTE : All given equations before should be parsed by ParseEq function
Implementation file : EqSimplifier.c
*/
#include "EqParser.h"
#ifndef _EQ_SIMPLIFIER_H_
#pragma once
#define _EQ_SIMPLIFIER_H_
typedef struct
{
	float num;
	bool isVar;
}Result;
Result GetResult(Node* node);
float SloveEq(char* eq, int size);
#endif