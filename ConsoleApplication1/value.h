#pragma once
#include <stdarg.h>
#include <stdlib.h>

typedef struct value
{
	int type; //type of value
	int ival; //int value
	double dval; //double value
	char *sval; //string/variable value
} Value;

extern void Fatal(char *, ...);
extern Value *newValue(void);

extern int INTEGER;
extern int REAL;
extern int STRING;
extern int VARIABLE;

extern Value *newValueI(int);
extern Value *newValueR(double);
extern Value *newValueS(char *);
extern Value *newValueV(char *);

extern void displayValue(Value *);
