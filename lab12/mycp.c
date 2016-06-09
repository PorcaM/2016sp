#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"

int main (int argc, char** argv)
{
	char* buf = NULL;
	int fsize, ret;
	FILE *files[2];
	int fd[2];

	/* check arguments */
	if (argc != 3) {
		printf ("usage: mycp src dst\n");
		exit (-1);
	}

	/* TODO: Add your code here */
	files[0] = fopen (argv[1], "r");
	files[1] = fopen (argv[2], "w");
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[2], O_WRONLY);

	fsize = get_size (files[0]);
	printf ("%s size is: %d\n", argv[1], fsize);
	copy (fd[0], fd[1], fsize);
	printf ("%s is copied to %s (%d bytes)\n", argv[1], argv[2], fsize);

	return 0;
}

