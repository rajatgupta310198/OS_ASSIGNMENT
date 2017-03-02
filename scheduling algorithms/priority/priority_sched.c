#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
int main()
{
	struct queue readyq;
	initq(&readyq);
	struct PCB pcb;
	int i,n,pri;
	float t;
	printf("Enter number of process :");
	scanf("%d",&n);
	for(i=0;i<n;i++)
		{
			pcb.pid = i+1;
			pcb.in_time = rand()%100;
			pcb.burst =  10 - (float)rand()/RAND_MAX;
			pcb.priority = 1+rand()%4;
			enq(&readyq,pcb);
		}
 	printf("\n");
	traverse(&readyq);
	return 0;
}
