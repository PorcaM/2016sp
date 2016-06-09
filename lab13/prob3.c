#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "sbuf.h"

#define SBUFSIZE 1000000

void* producer (void* arg)
{
	sbuf_t* sbuf = (sbuf_t*)arg;
	int i = 0;
	double item;

	for (i = 0; i < SBUFSIZE; i++) {
		item = i;
		sbuf_insert (sbuf, item); 
	}
}

void* consumer (void* arg)
{
	sbuf_t* sbuf = (sbuf_t*)arg;
	int i = 0;
	double item;

	for (i = 0; i < SBUFSIZE; i++) {
		if ((item = sbuf_remove (sbuf)) != i) {
			printf ("oops! %f != %d\n", item, i);
			exit (-1);
		}
	}
}

int main (int argc, char** argv)
{
	int i, num_threads;
	pthread_t* pthreads = NULL;
	pthread_t* cthreads = NULL;
	sbuf_t* sbufs = NULL;
	
	if (argc != 2) {
		printf ("usage: %s <# of threads>\n", argv[0]);
		exit (-1);
	}
	num_threads = atoi (argv[1]);
	pthreads = (pthread_t*)malloc (sizeof (pthread_t) * num_threads);
	cthreads = (pthread_t*)malloc (sizeof (pthread_t) * num_threads);
	sbufs = (sbuf_t*)malloc (sizeof (sbuf_t) * num_threads);

	for (i = 0; i < num_threads; i++) {
    	sbuf_init (&sbufs[i], SBUFSIZE); 
		/* create a producer */
		pthread_create (&pthreads[i], NULL, producer, (void*)&sbufs[i]);
		/* create a consumer */
		pthread_create (&cthreads[i], NULL, consumer, (void*)&sbufs[i]);
	}

	for (i = 0; i < num_threads; i++) {
		pthread_join (pthreads[i], NULL);
		pthread_join (cthreads[i], NULL);
	}

	free (pthreads);
	free (cthreads);
	free (sbufs);

	return 0;
}

