#include <stdio.h>
#include <omp.h>

int main(){
	omp_set_num_threads(4);
	const int N = 28;
	int nthreads, threadid, i;
	double a[N],b[N],result[N];
	for(i=0;i<N;i++){
		a[i]=1.0*i;
		b[i]=2.0*i;
	}
	int chunk = 7;
	
	#pragma omp parallel private(threadid)
	{//fork

	threadid = omp_get_thread_num(); //fetch the threadid

	#pragma omp for schedule(dynamic,chunk)
	for (i=0; i<N ; i++){
		result[i] = a[i] + b[i];
		printf("Thread id : %d working on index %d\n",threadid, i);
	}
	
	}//join
	
	printf("TEST result[19] = %g\n",result[19]);
	
	return 0;
}
