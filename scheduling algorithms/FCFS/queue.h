#ifndef QUEUE_H
#define QUEUE_H 

#include <stdlib.h>
#include <stdio.h>
#include "pcb.h"
struct node
{
	struct PCB pcb;
	struct node *next;
};
struct queue{
  struct node *front,*rear;
  int no_of_process;
};
void initq(struct queue *q)
{
	q->front =NULL;
	q->rear = NULL;
	q->no_of_process = 0;
}
void enq(struct queue *q, struct PCB pcb)
{	
	struct node *t = (struct node*)malloc(sizeof(struct node));
	t->pcb = pcb;
	t->next  = NULL;
	q->no_of_process +=1; 
	if(q->rear==NULL)
	{   t->pcb.wait_time = 0;
		q->front = t;
		q->rear = t;
	}
	else
	{   t->pcb.wait_time = q->rear->pcb.burst + q->rear->pcb.wait_time;
		q->rear->next = t;
		q->rear = t;
	}
	// enq operation 
}
void deq(struct queue *q)
{
	if(q->front!=NULL)
	{
		struct node *t = q->front;
		q->front = q->front->next;
		free(t);
		if(q->front==NULL)
			q->rear = NULL;
		q->no_of_process--;
	}
  	// deq oeration
}
void traverse(struct queue *q)
{	struct node * t = q->front;
	printf("PID\tIn Time\tBurst Time\tWait Time\tTurn Around Time\n");
	float avg_wait = 0;

	while(t!=NULL)
	{	
		avg_wait += t->pcb.wait_time;
		avg_wait = avg_wait/q->no_of_process;
		t->pcb.turn_around_time = t->pcb.burst + t->pcb.wait_time;
		printf("%d\t%.2f\t%.2f\t\t%.2f\t\t%.2f\n",t->pcb.pid,t->pcb.in_time,t->pcb.burst,t->pcb.wait_time,t->pcb.turn_around_time);
		t = t->next;
	}
	printf("Average wait time : %.2f\n",avg_wait);
	// traverse q
}

#endif