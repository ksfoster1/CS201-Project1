#include<stdio.h>
#include<stdlib.h>
#include "queue.h"
#include "value.h"
#include "node.h"

Queue *createQueue()
{
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->front = q->rear = NULL;
	q->count = 0;
	return q;
}

void enqueue(Queue *q, Value *v)
{
	if (q->rear == NULL)
		{
			q->rear = newNode(v, NULL);
			q->front = q->rear;
		}
	else
		{
			q->temp = newNode(v, NULL);
			q->rear->next = q->temp;
			q->rear = q->temp;
		}
	q->count+=1;
	printf("COUNT = %d", q->count);
}

Value *dequeue(Queue *q)
{
	//q->temp = q->front;
	Value *tempValue = newValue();

	if (q->front == NULL)
	{
		printf("\n Error: Trying to display elements from empty queue");
		return NULL;
	}

	else
	{
			//printf("\n Dequeued value : ");
			displayValue(q->front->v);
			tempValue = q->front->v;
			q->front = q->front->next;
			return tempValue;
	}

	q->count--;
}

void printQ(Queue *q)
{
	q->front1 = q->front;
	printf("Queue: ");
	//printf("COUNT: %d", COUNT);

	if (q->count == 0)
		printf("Queue Empty!!\n");
	if (q->count == 1)
	{
		displayValue(q->front1->v);
	}
	while (q->front1 != q->rear)
	{
		displayValue(q->front1->v);
		q->front1 = q->front1->next;
	}

	if (q->front1 == q->rear)
		displayValue(q->front1->v);
}