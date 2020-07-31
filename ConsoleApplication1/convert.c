#pragma once
#define _CRT_NONSTDC_NO_WARNINGS //because visual studio
#define _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS_GLOBALS 
#include "value.h"
#include "node.h"
#include "queue.h"
#include "stack.h"
#include "convert.h"
#include "BST.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

Stack *infix_to_postfix(Queue *q)
{
	Stack *s = createStack(); //postfix stored in a stack
	Stack *TS = createStack(); //temp stack 
	Value *tempVQ = newValue(); //temp value dequeued from queue

	q->front1 = q->front;

	while (q->front1)
	{
		printf("GGGGGG");
		tempVQ = dequeue(q);
		if (q->front1 == q->rear)
		{
			push(s, tempVQ); //push onto postfix
			break;
		}
		//if int or real or var or string that is not an operator
		if (tempVQ->type == 0 || tempVQ->type == 1 || tempVQ->type == 3 || (operator(tempVQ->sval) == 0))
			push(s, tempVQ); //push onto postfix
		else
			if (strcmp(tempVQ->sval, "(") == 0)
				push(TS, tempVQ); //push onto temp stack
			else
				if (strcmp(tempVQ->sval, ")") == 0)
				{
					while (strcmp((tempVQ = pop(TS))->sval, "(") != 0)
					{
						push(s, tempVQ);
						printf("TTTTTTTTTT");
					}

					while (TS->top != NULL && precedence(tempVQ->sval) <= precedence(TS->top->v->sval))
					{
						printf("mmmm");
						//push(s, tempVQ);
						tempVQ = pop(TS);
						push(s, tempVQ);
						printf("\n");
						displayValue(tempVQ);
					}
				}

				else
				{
					//push(TS, tempVQ);
					if (TS->top != NULL && precedence(tempVQ->sval) <= precedence(TS->top->v->sval))
					{
						Value *m = newValue();
						m = tempVQ;
						while (TS->top != NULL && precedence(tempVQ->sval) <= precedence(TS->top->v->sval))
						{

							printf("mmmm");
							
							tempVQ = pop(TS);
							push(s, tempVQ);
						}
						push(TS, m);
					}
					else
					{
						push(TS, tempVQ);
					}
				}

		q->front1 = q->front1->next;
	}

	while (TS->top != NULL) //sends everything from temp stack to postfix
	{
		tempVQ = pop(TS);
		push(s, tempVQ);
	}

	return s;
}

int operator(char *v)
{
	if (strcmp(v, "+") == 0 || strcmp(v, "-") == 0 || strcmp(v, "*") == 0 //check if an operator
		|| strcmp(v, "/") == 0 || strcmp(v, "%") == 0 || strcmp(v, "^") == 0
		|| strcmp(v, "(") == 0 || strcmp(v, ")") == 0)
		return 1;
	else
		return 0;
}

int precedence(char *v)
{
	if (strcmp(v, "(") == 0)
		return 0;
	if (strcmp((const char *)v, "=") == 0)
		return 1;
	if (strcmp((const char *)v, "+") == 0)
		return 2;
	if (strcmp((const char *)v, "-") == 0)
		return 3;
	if (strcmp((const char *)v, "*") == 0)
		return 4;
	if (strcmp((const char *)v, "/") == 0)
		return 5;
	if (strcmp((const char *)v, "%") == 0)
		return 6;
	if (strcmp((const char *)v, "^") == 0)
		return 7;

	return 8; 
}

Stack *postfix_to_literal(Stack *s, BSTNode *b) //print literal at end //add variable checking
{
	Stack *newStack = createStack();
	Value *tempVS = newValue(); 
	Value *value = newValue();
	Value *o1 = newValue();
	Value *o2 = newValue();
	s->top1 = s->top;

	while (s->top1 != NULL)
	{
		printf("COUNT FOR S %d", s->count);
		if (s->count == 2)
		{
			printf("mmm");
			value = pop(s);
			char *temp = value->sval;
			value = search(b, temp);
			push(newStack, value);
			break;
		}

		tempVS = pop(s);

		if (tempVS->type == 0 || tempVS->type == 1 || tempVS->type == 3 || (operator(tempVS->sval) == 0))
			push(newStack, tempVS); //push onto temp stack for literal
		else // if string (operator or string) //if var find value in BST
		{
			o2 = pop(newStack);
			o1 = pop(newStack);

			if (o1->type == 3)
			{
				o1 = search(b, o1->sval); //replace temp variable value with actual value
				printf("SVAL is %s", o1->sval);
				//value = o1;
			}

			if (o2->type == 3)
			{
				o2 = search(b, o2->sval); //replace temp variable value with actual value
				printf("SVAL is %s", o2->sval);
				//value = o2;
			}

			if (o1->type == 2 && o2->type == 2) //if adding two strings //return string
			{
				char *c = malloc(sizeof(char) * (strlen(o1->sval) + strlen(o2->sval) + 1));
				if (c == 0) Fatal("out of memory\n");
				sprintf(c, "\"%s%s\"", o1->sval, o2->sval);
				value = newValueS(c);
				push(newStack, value);
			}

			else if (o1->type == 0 && o2->type == 0) //if dividing two ints //returns int
			{
				if (strcmp(tempVS->sval, "/") == 0)
				{
					int i = (o1->ival) / (o2->ival);
					value = newValueI(i);
					displayValue(value);
					push(newStack, value);
				}
				else
				{
					double fval = evaluate(tempVS->sval, (double)o1->ival, (double)o2->ival);
					int i = (int) fval;
					value = newValueI(i);
					displayValue(value);
					push(newStack, value);
				}

			}

			else if (o1->type == 1 && o2->type == 1) //if adding two reals //returns real
			{
				double fval = evaluate(tempVS->sval, o1->dval, o2->dval);
				value = newValueR(fval);
				push(newStack, value);
			}

			else if (o1->type == 0 && o2->type == 1) //if adding a int and a real //returns real
			{
				double f = (double)(o1->ival);
				double fval = 0.0;
				fval = evaluate(tempVS->sval, f, o2->dval); //returns int
				value = newValueR(fval);
				push(newStack, value);
			}

			else if (o1->type == 1 && o2->type == 0) //if adding a real and a int //returns real
			{
				double f = (double)(o2->ival);
				double fval = 0.0;
				fval = evaluate(tempVS->sval, o1->dval, f); //returns int
				value = newValueR(fval);
				push(newStack, value);
			}

			else if (o1->type == 2 && o2->type == 1) //if adding a string and a real
			{
				double f = atof(o1->sval);
				double fval = 0.0;
				fval = evaluate(tempVS->sval, f, o2->dval); //returns int
				value = newValueR(fval);
				push(newStack, value);
			}
			else if (o1->type == 1 && o2->type == 2) //if adding a real and a string
			{
				double f = atof(o2->sval);
				double fval = 0.0;
				fval = evaluate(tempVS->sval, o1->dval, f); //returns int
				value = newValueR(fval);
				push(newStack, value);
			}

			else if (o1->type == 0 && o2->type == 2) //if adding a int and a string
			{
				int i = atoi(o2->sval);
				double fval = 0.0;
				fval = evaluate(tempVS->sval, o1->ival, (double)i); 
				value = newValueI((int)fval);
				push(newStack, value);
			}

			else if (o1->type == 2 && o2->type == 0) //if adding a string and a int
			{
				int i = atoi(o1->sval);
				double fval = 0.0;
				fval = evaluate(tempVS->sval, (double)i, (double)o2->ival);
				value = newValueI((int)fval);
				push(newStack, value);
			}
			else //var by itself?
				push(newStack, value);
		}
	s->top1 = s->top1->next;
	}
	return newStack;
	printS(newStack); //print literal from stack
}

double evaluate(char *sval, double op1, double op2)
{
	if (strcmp(sval, "=") == 0)
		return(op1 + op2);
	if (strcmp(sval, "+") == 0)
		return(op1 + op2);
	if (strcmp(sval, "-") == 0)
		return(op1 - op2);
	if (strcmp(sval, "*") == 0) 
		return(op1*op2);
	if (strcmp(sval, "/") == 0)
		return(op1 / op2);
	if (strcmp(sval, "%") == 0)
		return(fmod(op1,op2));
	if (strcmp(sval, "^") == 0)
		return(pow(op1,op2));
	else
		return 0;
}