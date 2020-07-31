#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "value.h"
#include "node.h"

Stack *createStack()
{
	Stack *s = malloc(sizeof(Stack));
	s->top = NULL;
	s->count = 0;
	return s;
}

void push(Stack *s, Value *v)
{
	if (s->top == NULL)
	{
		s->top = newNode(v, NULL);
		s->count++;
	}
	else
	{
		s->temp = s->top;
		s->top = newNode(v, s->temp);
		s->count++;
	}
}
Value *pop(Stack *s)
{
	//s->top1 = s->top;
	Value *tempV = newValue();

	if (s->top == NULL)
	{
		printf("\n Error : Trying to pop from empty stack");
		return NULL;
	}
	else
	{
		//s->top1 = s->top1->next;
		printf("\n Popped value : ");
		displayValue(s->top->v);
		tempV = s->top->v;
		s->top = s->top->next;
		return tempV;
		s->count--;
	}
}

void printS(Stack *s)
{
	s->top1 = s->top;
	printf("Stack: ");

	if (s->count == 0)
		printf("Stack Empty!!\n");
	if (s->count == 1)
	{
		displayValue(s->top1->v);
	}
	else
	{
		while (s->top1 != NULL)
		{
			displayValue(s->top1->v);
			s->top1 = s->top1->next;
		}
	}
}

void reverseStack(Stack *s)
{
	if (s->top != NULL)
	{
		Value *v = newValue();
		v = pop(s);
		reverseStack(s);
		bottom(s, v);
	}
}
void bottom(Stack *s, Value *v)
{
	if (s->top == NULL)
		push(s, v);
	else
	{
		Value *vt = newValue();
		vt = pop(s);
		bottom(s, v);
		push(s, vt);
	}
}