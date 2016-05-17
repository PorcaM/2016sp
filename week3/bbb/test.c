#include <stdio.h>

typedef unsigned char *pointer;


void displayHex(pointer start, int len){
	int i;
	for(i = 0 ; i < len; i++){
		printf("%.2x ", start[i]);
	}
	printf("\n");
}

void displayBin(pointer start,int len){
	int i, j, temp;
	temp = *start;
	for(i = 0; i < len; i++){
		temp = start[i];
		for(j = 0; j < 8; j++){
			if(temp&0x80) printf("1");
			else printf("0");	
			temp = temp<<1;
			if(j%4 == 3) printf(" ");
		}
	}	
	printf("\n");
}

void lsb_msb(pointer start,int len){
	int temp = *start;
	printf("LSB is ");
	displayBin(start, 1);
	printf("MSB is ");
	displayBin(start+3, 1);
}
unsigned int inverse_bit(pointer start,int len){
	int i, j, temp;
	for(i = 0; i < len; i++){
		temp = start[len-i-1];
		for(j=0; j < 8; j++){
			printf("%d",temp&1);
			temp = temp>>1;
			if(j%4 == 3) printf(" ");
		}
	}
	printf("\n");
}


 int swap (int* x, int* y) {
	*x = *y^*x;
	*y = *y^*x;
	*x = *y^*x;
  }

int partial_multi (int x, int y)
{
	int i, j, temp1=0, temp2=0;
	y = y>>8;
	x = x&0x0F;
	y = y&0x0F;
	return x*y;
}

void main(int argc, char** argv)
{
	int a = 14213;	
	int b = 19352;	
		
	printf("\n---dispaly Decimal---\n");
	printf("int a = %d\n", a);
	printf("int b = %d\n", b);

	printf("\n---1. dispaly Hex---\n");
	displayHex((pointer) &a , sizeof(int));
	displayHex((pointer) &b , sizeof(int));

	printf("\n---2. dispaly Binary---\n");	
	displayBin((pointer) &a , sizeof(int));	
	displayBin((pointer) &b , sizeof(int));	

	printf("\n---3. print LBS/MBS---\n");
	lsb_msb((pointer) &a , sizeof(int));
	lsb_msb((pointer) &b , sizeof(int));

	printf("\n---4. Inverse value---\n");
	inverse_bit((pointer) &a , sizeof(int));
	inverse_bit((pointer) &b , sizeof(int));

	printf("\n---5. partial Multiplication---\n");
	printf ("%d\n", partial_multi (a, b));

	printf("\n---6. swap 연산---\n");
	printf("a=%d, b=%d\n",a,b);
	swap(&a,&b);
	printf("a=%d, b=%d\n",a,b);		
}
