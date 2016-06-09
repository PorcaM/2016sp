#include <semaphore.h>

typedef struct {
	/* TODO: Add something here */
	double	value;
} sbuf_t;

/* create an empty, bounded, shared FIFO buffer with n slots */
void sbuf_init(sbuf_t *sp, int n);

/* clean up buffer sp */
void sbuf_deinit(sbuf_t *sp);

/* insert item onto the rear of shared buffer sp */
void sbuf_insert(sbuf_t *sp, double item);

/* remove and return the first item from buffer sp */
double sbuf_remove(sbuf_t *sp);
