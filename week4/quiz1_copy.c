#include <stdio.h>

int main(){
	int a, b;
	a = 8;
	a = a >> 2;
	b = a;
	a = a << 2;
	a = a+b;
	printf("%d\n",a);
	return 0;
}
