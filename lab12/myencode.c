#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"

int main (int argc, char** argv)
{
	char* buf = NULL;
	int fsize, ret;
	FILE *file;
	int fd[2];
	char key;

	/* check arguments */
	if (argc != 4) {
		printf ("usage: myencode src dst key\n");
		exit (-1);
	}

	/* TODO: Add your code here */
	file	= fopen (argv[2], "w");
	file	= fopen (argv[1], "r");
	fsize	= get_size (file);
	key		= atoi(argv[3]);
	printf ("input key (one byte): 0x%X\n", key);

	fd[0]	= open (argv[1], O_RDONLY);
	fd[1]	= open (argv[2], O_WRONLY);

	my_encode (fd[0], fd[1], fsize, key);

	printf ("%s is encodded to %s (%d bytes)\n", argv[1], argv[2], fsize);

	return 0;
}

