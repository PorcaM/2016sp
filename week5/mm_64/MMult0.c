#include <stdio.h>


#define A(i,j) a[ (i)*n + (j) ]
#define B(i,j) b[ (i)*n + (j) ]
#define C(i,j) c[ (i)*n + (j) ]

/* Routine for computing C = A * B + C */

void MY_MMult( int n, double *a, double *b, double *c)
{
	int i, j, k, size, div, left;
/*
	for ( i=0; i<n; i++ ){
		for ( j=0; j<n; j++ ){
			for ( k=0; k<n; k++ ){
				C( i,j ) = C( i,j ) +  A( i,k ) * B( k,j );
			}
		}
	}
*/
	mult_kij(n,a,b,c,0,0,n);
	
/*
	size = 100;
	div = n/size; left = n%size;
	for(i = 0; i < div; i++){
		for(j = 0 ; j < div; j++){
			mul(n,a,b,c,i*size,j*size,size);
		}
	//	printf("\n");
	}
*/
	
}

void mul(int n, double *a, double *b, double *c, int x, int y, int s){
	int i, j, k;
	int yi, xk, xj, yk;
	register double r;
	for(i = 0; i < s; i++){
		for(j = 0; j < s; j++){
			yi = y+i; xj = x+j;
			r = C(yi,xj);
			for(k= 0 ; k < s; k++){
				xk = x+k; yk = y+k, xj = x+j; yi = y+i;
				r += A(yi, xk) * B(yk, xj);
			}
			C(yi,xj) += r;
		}
	}
}

void mult_kij( int n, double *a, double *b, double *c, int x, int y, int s){
	int i, j, k;
	int yi, xk, xj, yk;
	register double r;
	
//	printf("%s %d %d %d ", "kij", x, y, s);

	for( i=0; i<s; i++){
		for( k=0; k<s; k++ ){
			yi = y+i; xk = x+k;
			r = A( yi, xk );
			for( j=0; j<s; j++){
				yi = y+i; xj = x+j; yk = y+k;
				C( yi,xj ) += r * B( yk,xj );
			}
		}
	}
}
