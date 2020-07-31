#pragma once
#include "node.h"
#include "value.h"

typedef struct stack
{
	struct node *top;
	struct node *temp;
	struct node *top1;
	int count;
} Stack;

extern Stack *createStack(); //creates empty stack
extern void push(Stack *, Value *);
extern Value *pop(Stack *);
extern void printS(Stack *);
extern void reverseStack(Stack *);
extern void bottom(Stack *, Value *);
