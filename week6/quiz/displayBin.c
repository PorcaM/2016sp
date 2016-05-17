#include <stdio.h>

void displayBin(unsigned char *p, int size){
	int i, j, temp;	
	for(i = 0; i < size; i++){
		temp = p[i];
		for(j = 0; j < 8; j++){
			printf("%d", (temp&0x80)>>7);
			temp = temp<<1;
			if(j%4==3)
				printf("\t");
		}
	}
	printf("\n");
}
