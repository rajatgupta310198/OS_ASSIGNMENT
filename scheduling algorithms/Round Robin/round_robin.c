#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "queue.h"
#include "list.h"
int main()
{	int n,i;
	struct queue readyq;
	struct list mylist_of_process; // list of processes 
	initL(&mylist_of_process);
	initq(&readyq); // create empty ready queue
	struct PCB pcb;
	printf("Enter number of process :");
	scanf("%d",&n);
	for(i=0;i<n;i++)
		{
			pcb.pid = i+1;
			pcb.in_time = rand()%100;
			pcb.burst = 10 - (float)rand()/RAND_MAX;
			insert(&mylist_of_process,pcb);
		}
	sort(&mylist_of_process);
	enq(&readyq,&mylist_of_process); // fill ready queue
 	printf("\n");
	traverse(&readyq);
	return 0;
}