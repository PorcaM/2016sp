#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include "compute.h"

#define segfault	1
#define arithfault	2

#define _try\
	{\
	if(!sigsetjmp(buf, 1)){

#define _catch(type)\
	}else if(err==type){\
		err=0;

#define _throw(type)\
	err = type;\
	siglongjmp(buf,1);

#define _etry\
	}}

int err=0;
sigjmp_buf buf;

int run_compute (char* fname, int (*fn) (void))
{
	int ret;
	_try {
		printf ("\n--------------------------------\n");
		printf ("%s begins\n", fname);
		ret = fn ();
		printf ("%s returns %d\n", fname, ret);
		printf ("%s done\n", fname);
	} _catch (segfault) {
		printf ("caught a segmentation fault\n");
	} _catch (arithfault) {
		printf ("caught an arithmetic fault\n");
	}
	_etry

	return ret;
}

void segv_handler(int sig){
	_throw(segfault);
}
void fpe_handler(int sig){
	_throw(arithfault);
}	

int main (int argc, char** argv)
{
	signal(SIGSEGV, segv_handler );
	signal(SIGFPE, fpe_handler);

	run_compute ("compute1()", compute1);
	run_compute ("compute2()", compute2);
	run_compute ("compute3()", compute3);
	run_compute ("compute4()", compute4);
	run_compute ("compute5()", compute5);

	return 0;
}

