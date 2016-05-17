#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include "compute.h"

sigjmp_buf buf;

/* TODO: Implement your own code here */
void segv_handler(int sig){
	printf("oops! segmentation fault occurs!\n");
	siglongjmp(buf, 1);
}

void fpe_handler(int sig){
	printf("oops! floating point exception occurs!\n");
	siglongjmp(buf, 1);
}

int run_compute (char* fname, int (*fn) (void))
{
	int ret;

	/* TODO: Implement your own code here */
	if(!sigsetjmp(buf, 1)){
		printf ("\n--------------------------------\n");
		printf ("%s begins\n", fname);
		ret = fn ();
		printf ("%s returns %d\n", fname, ret);
		printf ("%s done\n", fname);
	}
	else 
		return -1;
	return ret;
}

int main (int argc, char** argv)
{
	signal(SIGSEGV, segv_handler);
	signal(SIGFPE, fpe_handler);

	run_compute ("compute1()", compute1);
	run_compute ("compute2()", compute2);
	run_compute ("compute3()", compute3);
	run_compute ("compute4()", compute4);
	run_compute ("compute5()", compute5);

	return 0;
}
