#include <stdio.h>
#include <stdlib.h>


int main (int argc, char** argv)
{
	unsigned char** buf = NULL;
	int* fsize;
	int ret, nr_srcfiles, i;
	char key;
	FILE *file;

	/* check arguments */
	if (argc < 4) {
		printf ("usage: mymerge mergedfile key srcfile1 srcfile2 ...\n");
		exit (-1);
	}

	/* TODO: Add your code here */
	int n = argc-3;
	printf("n:%d\n", n);
	key = atoi(argv[2]);
	printf ("input key (one byte): 0x%X\n", key);

	file = fopen (argv[1], "w");

	int *fd = (int *)malloc(n*sizeof(int));
	int i = 0;
	for (i = 0; i < n; i++){
		fd[i] = open(argv[3+i], O_RDONLY);
	}

	my_merge();

	printf ("%s is encodded to %s (%d bytes)\n", argv[1], argv[2], fsize);


	return 0;
}

