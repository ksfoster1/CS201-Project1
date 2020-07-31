#pragma once
#include "queue.h"
#include "stack.h"
#include "BST.h"


extern int operator(char *);
extern Stack *infix_to_postfix(Queue *);
extern int precedence(char *);
extern Stack *postfix_to_literal(Stack *, BSTNode *);
extern double evaluate(char *, double, double);

