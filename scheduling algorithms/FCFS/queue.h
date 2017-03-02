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
	{   
		q->front = t;
		q->rear = t;
	}
	else
	{   
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
void sort(struct queue *q)
{
	int i,j;
	struct node *t = q->front;
	while(t->next!=NULL)
	{
		struct node *t2 = t->next;
		while(t2)
		{
			if(t->pcb.in_time>t2->pcb.in_time)
			{
				struct PCB temp_pcb = t->pcb;
				t->pcb = t2->pcb;
				t2->pcb = temp_pcb;

			}
			t2 = t2->next;
		}
		t =t->next;
	}
	q->front->pcb.wait_time = 0;
	struct node *temp1 = q->front->next;
	struct node *temp2 = q->front;
	while(temp1)
	{
		temp1->pcb.wait_time = temp2->pcb.burst + temp2->pcb.wait_time;
		temp1=temp1->next;
		temp2 = temp2->next;
	}
}
void traverse(struct queue *q)
{	sort(q);
	struct node * t = q->front;
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
