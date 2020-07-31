//node.h
#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "value.h"

typedef struct node
{
	Value *v; //value object
	struct node *next;
} Node;

extern Node *newEmptyNode(void);
extern Node *newNode(Value *, Node *);
