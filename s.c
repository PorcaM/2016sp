#include <stdlib.h>

#include "sbuf.h"

sem_t key, full, empty;
sbuf_t *inp = NULL;
int j, it;
int size;

/* create an empty, bounded, shared FIFO buffer with n slots */
void sbuf_init(sbuf_t *sp, int n)
{
	int i;
	/* TODO: Add something here */
	size = n;
	it = j = 0;
	if(inp != NULL)
		sp = inp;
	else
		sp = malloc (sizeof (sbuf_t) * n);
	printf("sp: %p\n", sp);
	for (i = 0; i < n; i++){
	}
	sem_init (&key, 0, 1);
	sem_init (&full, 0, 0);
	sem_init (&empty, 0, n);
}

/* clean up buffer sp */
void sbuf_deinit(sbuf_t *sp)
{
	/* TODO: Add something here */
	free(sp);
}

/* insert item onto the rear of shared buffer sp */
void sbuf_insert(sbuf_t *sp, double item)
{
	/* TODO: Add something here */
	sem_wait (&empty);
	sem_wait (&key);

	sp[j].value = item;
//	printf("insert[%d]: %f\n", j, sp[j].value);
	j = (j+1)%size;

//	printf("i: %d, j: %d\n", it, j);

	sem_post (&full);
	sem_post (&key);
}

/* remove and return the first item from buffer sp */
double sbuf_remove(sbuf_t *sp)
{
	/* TODO: Add something here */
	double ret;
	sem_wait (&full);
	sem_wait (&key);
	
	ret = sp[it].value;
//	printf("remove[%d]: %f\n", it, sp[it].value);
	it = (it+1)%size;

//	printf("i: %d, j: %d\n", it, j);

	sem_post (&empty);
	sem_post (&key);

	return ret;
}

