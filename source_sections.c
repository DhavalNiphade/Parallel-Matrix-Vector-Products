#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(){
	const int N = 1000;
	int x[N],i,max_x,min_x,sum,sum2,threadid;
	float mean,mean2,var;
	max_x=0;
	min_x=0;
	sum=0;
	sum2=0;
	
	omp_set_num_threads(1);

	/*initialize x*/
	srand(1.0);
	#pragma omp parallel for
	for(i=0; i<N ; i++)
		x[i]=rand();
	
	#pragma omp parallel private(i,threadid) shared(x)
	{
	#pragma omp sections
	{
	/* fork 3 different threads*/
		{
		 for(i=0;i<N;i++){
			if(x[i] > max_x) max_x = x[i];
			if(x[i] < min_x) min_x = x[i];
		 }
		 printf("The max of x = %d\n",max_x);
		 printf("The min of x = %d\n",min_x);
		}
	#pragma omp section
	{/*calculate the mean of x*/
		printf("\nThread ID = %d\n",omp_get_thread_num());
		for(i=0;i<N;i++)
			sum = sum + x[i];
		mean = sum/N;
		printf("Mean of x = %f\n",mean);
	}//close section
	
	#pragma omp section
	{
		printf("\nThread ID = %d\n",omp_get_thread_num());
		for(i=0;i<N;i++)
			sum2 = sum2 + x[i] * x[i];
		mean2 = sum2/N;
	}//close section

	}//close all sections



	}//join

	var = mean2 - mean*mean;
	printf("Variance of x = %f\n",var);	
	return 0;
}
