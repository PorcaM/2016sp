#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "compute.h"

void segv_handler(int sig){
	printf("segmentation fault occurs!\n");
	exit(0);
}

int main (int argc, char** argv)
{
	/* TODO: Impelement your code here */
	signal(SIGSEGV, segv_handler);
	int *p = NULL;
	p[10] = 5;
	free(p);

	return 0;
}

