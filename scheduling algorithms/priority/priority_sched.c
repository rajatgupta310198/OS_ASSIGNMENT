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
			pcb.in_time = i;
			printf("\nEnter in burst time :");
			scanf("%f",&t);
			printf("\nEnter in prority :");
			scanf("%d",&pri);
			pcb.burst = t;
			pcb.priority = pri;
			enq(&readyq,pcb);
		}
 	printf("\n");
	traverse(&readyq);
	return 0;
}