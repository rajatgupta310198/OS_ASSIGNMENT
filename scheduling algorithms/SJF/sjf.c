#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
int main()
{
	struct queue readyq;
	initq(&readyq);
	struct PCB pcb;
	int i,n;
	printf("Enter number of process :");
	scanf("%d",&n);
	for(i=0;i<n;i++)
		{
			pcb.pid = i+1;
			pcb.in_time = i;
			printf("\nEnter in burst time :");
			float t;
			scanf("%f",&t);
			pcb.burst = t;
			enq(&readyq,pcb);
		}
 	printf("\n");
	traverse(&readyq);
	return 0;
}