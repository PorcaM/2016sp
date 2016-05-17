#include <stdio.h>

void displayHex(unsigned char *p, int size){
	int i;	
	for(i = 0; i < size; i++){
		printf("%x\t", p[i]);
	}
	printf("\n");
}
