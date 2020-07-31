#pragma once
#include "node.h"
#include "value.h"

typedef struct queue
{
	struct node *front;
	struct node *rear;
	struct node *temp;
	struct node *front1;
	int count;
} Queue;

extern Queue *createQueue(); //creates empty queue
extern void enqueue(Queue *, Value *);
extern Value *dequeue(Queue *);
extern void printQ(Queue *);
