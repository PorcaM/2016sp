#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char** argv)
{
	FILE* fsrc = NULL;
	unsigned char** buf = NULL;
	char fname[10][256];
	int* fsize;
	int ret, nr_srcfiles, i;
	char key;

	/* check arguments */
	if (argc != 3) {
		printf ("usage: mysplit src key\n");
		exit (-1);
	}

	/* TODO: Add your code here */

	return 0;
}

