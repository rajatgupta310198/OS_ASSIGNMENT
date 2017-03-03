#ifndef LIST_H
#define LIST_H
#include "pcb.h"

struct list{
	struct node *head;
};
struct node
{
	struct PCB pcb;
	struct node *next;
};
void initL(struct list *l)
{
	l->head = NULL;
}
void insert(struct list *l,struct PCB pcb)
{
	struct node *t = (struct node*)malloc(sizeof(struct node));
	t->pcb = pcb;
	if(l->head == NULL)
	{
		l->head = t;
	}
	else
	{
		t->next = l->head;
		l->head = t;
	}
}
void sort(struct list *l)
{
	struct node *t = l->head;
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
}
void calc(struct list *l)
{
	struct node *t = l->head;
	while(t)
	{
		printf("%d\t%.2f\t\t%.2f\t\t%.2f\n",t->pcb.pid,t->pcb.in_time,t->pcb.wait_time,t->pcb.turn_around_time);
		t=t->next;
	}
}
void disp(struct list *l)
{	sort(l);
	if(l->head)
	{
		struct node *t = l->head;
		while(t)
		{
			printf("%d\t%.2f\n",t->pcb.pid,t->pcb.in_time);
			t = t->next;
		}
	}
}
#endif