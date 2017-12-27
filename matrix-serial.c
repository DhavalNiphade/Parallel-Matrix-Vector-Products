#include <stdio.h>
#include <omp.h>
#include <math.h>

#define size 10000

double A[size*size],x[size],b[size];

int main(){
	//const int size = 10000;
	int i,j;
	
	//double A[size*size];
	//double x[size],b[size];

	//Initialize the matrix and vector
	for(j=0;j<size;j++){
		for(i=0;i<size;i++){
			A[i+size*j] = sin(0.01*(i+size*j));
		}
	b[j] = cos(0.01*j);
	x[j] = 0.0;
	}

	//Matrix vector multiplication
	for(j=0;j<size;j++){
		for(i=0;i<size;i++){
			x[j] += A[i+size*j]*b[i];
		}
	}
	
	printf("x[%d] = %g\n",5050,x[5050]);
	//printf("x[%d] = %g\n",5,x[5]);

	return 0;
}
