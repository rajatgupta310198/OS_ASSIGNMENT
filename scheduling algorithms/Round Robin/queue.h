#ifndef QUEUE_H
#define QUEUE_H 

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

const float time_const = 1.00;
int original_no_of_proc;
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
void enq(struct queue *q, struct list *l)
{	
	
	struct node *temp = l->head;
	while(temp)
	{	struct node *t = (struct node*)malloc(sizeof(struct node));
		t->pcb = temp->pcb;
		t->next  = NULL;
		q->no_of_process +=1; 
		if(q->rear==NULL)
		{   
			t->pcb.wait_time = 0;
			q->front = t;
			q->rear = t;
		}
		else
		{   t->pcb.wait_time  = q->no_of_process*time_const; // initial wait time for each process
			q->rear->next = t;
			q->rear = t;
		}
		q->rear->next = q->front;
		temp = temp->next;
	}
	original_no_of_proc = q->no_of_process;
	// enq operation 
}
void deq(struct queue *q,struct list *l)
{
	if(q->front!=NULL)
	{
		struct node *t = q->front;
		q->front = q->front->next;
		q->rear->next = q->front;
		t->next = NULL;
		if(l->head == NULL)
		{
			l->head = t;
		}
		else{
			t->next = l->head;
			l->head = t;
		}
		free(t);
		if(q->front==q->rear)
			q->rear = q->front = NULL;
		q->no_of_process--;
	}
	else
	{
		printf("\n Empty");
	}
  	// deq oeration
}

void swapout(struct queue *q)
{
	struct node *t = q->front;
	q->front = t->next;
	t->next = q->front;
	q->rear->next = t;
	q->rear = t;
	
}
int is_empty(struct queue *q)
{
	if(q->front!=NULL)
	return 1;
	else
	return 0;
}
void traverse(struct queue *q)
{	
	
	struct list completed_proc_list;
	initL(&completed_proc_list);
	float time_adj = 0;
	printf("Gantt Chart\n");
	printf("PID\t\tIn Time\t\tWait Time\tTurn Around Time\n");
	float avg_wait = 0;
	int timest = 0;
	while(is_empty(q))
	{	struct node *t = q->front;
		if(t->pcb.burst<time_const)
		{
			time_adj += t->pcb.burst;
			deq(q,&completed_proc_list);
		}
		else
		{
			t->pcb.burst = t->pcb.burst - time_const;
			t->pcb.wait_time += time_const*(q->no_of_process-1) - time_adj;
			avg_wait +=t->pcb.wait_time;
			avg_wait /=original_no_of_proc; 
			t->pcb.turn_around_time = t->pcb.wait_time + t->pcb.burst;
			if(t->pcb.burst == 0)
			{
				deq(q,&completed_proc_list);
			}
			else
			{
				swapout(q);
			}
		}
	// traverse q
	}
	calc(&completed_proc_list);
	printf("\n\nAverage Waiting Time : %.2f\n",avg_wait);
}
void display(struct queue *q)
{	
	if(q->front)
	{
		printf("#\tPID\tIn Time\tBurst\n");
		struct node *t = q->front;
		int i=1;
		while(t->next!=q->front)
		{	
			printf("%d\t%d\t%.2f\t%.2f\n",i,t->pcb.pid,t->pcb.in_time,t->pcb.burst);
			t = t->next;
			i++;
		}
		printf("%d\t%d\t%.2f\t%.2f\n",i,t->pcb.pid,t->pcb.in_time,t->pcb.burst);
	}
	else
	{
		printf(" Empty Queue\n");
	}
}
#endif
