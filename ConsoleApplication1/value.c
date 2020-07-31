// value.c 
// holds each element of the expression
#define _CRT_NONSTDC_NO_WARNINGS //because visual studio
#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS_GLOBALS 

#include "value.h"
#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
#include <stdlib.h>

int INTEGER = 0;
int REAL = 1; 
int STRING = 2;
int VARIABLE = 3;

Value *newValueI(int i)
{
	Value *v = newValue();
	v->type = 0;
	v->ival = i;
	return v;
}

Value *newValueR(double d)
{
	Value *v = newValue();
	v->type = 1;
	v->dval = d;
	return v;
}

Value *newValueS(char *s) //operator
{
	Value *v = newValue();
	v->type = 2;
	v->sval = s;
	return v;
}

Value *newValueV(char *s) //holds both var name
{
	Value *v = newValue();
	v->type = 3;
	v->sval = s;
	return v;
}

void Fatal(char *fmt, ...)
{
	va_list ap;

	fprintf(stderr, "An error occured: ");
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	exit(-1);
}

Value *newValue(void) /* defaults to integer zero */
{
	Value *v;

	if ((v = malloc(sizeof(Value))) == 0)
		Fatal("out of memory\n");
	v->type = INTEGER;
	v->ival = 0;
	v->dval = 0;
	v->sval = 0;

	return v;
}

void displayValue(Value *v)
{
	if (v->type == 0)
	{
		//printf("\n Type is INTEGER ");
		printf("%d ", v->ival);
	}
	if (v->type == 1)
	{
		//printf("\n Type is REAL ");
		printf("%f ", v->dval);
	}
	if (v->type == 2)
	{
		//printf("\n Type is STRING ");
		printf("%s ", v->sval);
	}
	if (v->type == 3)
	{
		//printf("\n Type is VARIABLE ");
		printf("%s ", v->sval);
	}
}
