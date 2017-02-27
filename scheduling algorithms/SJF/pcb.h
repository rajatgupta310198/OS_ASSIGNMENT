#ifndef PCB_H
#define PCB_H 

struct PCB
{
	int pid;
	float in_time;
	float wait_time;
	float burst;
	float turn_around_time;
};

#endif