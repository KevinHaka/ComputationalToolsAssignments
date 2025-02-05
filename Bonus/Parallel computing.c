#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define random_num ((float)rand() / (float)RAND_MAX);

int main() {
	srand(time(NULL));
	
	int nThreads, i;
	long long int N, sum=0;

	scanf("%d", &nThreads);
	scanf("%lld", &N);
	
	int	seeds[nThreads];

	for (i=0; i<nThreads; i++) seeds[i] = rand();
	
	#pragma omp parallel num_threads(nThreads) shared(seeds,N,nThreads) reduction(+:sum) default(none)
	{
		long long int i;
		float x,y;

	    int thread_id = omp_get_thread_num();
	    long long int iStart = thread_id*N/nThreads;
	    long long int iEnd = (thread_id+1)*N/nThreads;
	    
	    srand(seeds[thread_id]);
	    
	    if (thread_id == nThreads - 1) iEnd = N;

		for (i=iStart; i<iEnd; i++) {
			x = random_num;
			y = random_num;
			
			if (x*x+y*y < 1.) sum++;
		}
	}

	printf("%.10f\n",(double) 4.*sum/N);
	return 0;
}