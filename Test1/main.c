#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// int main()
// {
	// printf("Number of processors available = %d\n",omp_get_num_procs());
	// double time_spent = 0.0;
	// clock_t begin = clock();
    // #pragma omp parallel
    // {
    	// printf("Hello world!\n");
    // }
	// clock_t end = clock();
	// time_spent += (double)(end - begin) / CLOCKS_PER_SEC * 1000;
	// printf("Time elpased is %f milliseconds\n\n\n", time_spent);
	
	// time_spent = 0.0;
	// clock_t begin1 = clock();
    // for(int i = 0;i < 128; i ++)
	// {
		// printf("Hello world!\n");
	// }
	// clock_t end1 = clock();
	// time_spent += (double)(end1 - begin1) / CLOCKS_PER_SEC * 1000;
	// printf("Time elpased is %f milliseconds\n\n\n", time_spent);
	
    
    // return 0;
// }

// int main(int argc, char* argv[])
// {
	// int id;
	// double wtime;
	// printf("Number of processors available = %d\n",omp_get_num_procs());
	// printf("Number of threads = %d\n",omp_get_max_threads());
	// wtime = omp_get_wtime();
	// printf("OUTSIDE Parallel region\n");
	
	// id = omp_get_thread_num();
	// printf("Hello from process %d\n Going into parallel zone \n",id);
	
	// #pragma omp parallel private(id) 
	// {
		// id = omp_get_thread_num();
		// printf("Hello from process number %d\n",id);
	// }
	
	// wtime = omp_get_wtime()-wtime;
	
	// printf("Back outside the parallel region\nTime elapsed = %f\n",wtime);
	// return 0;
// }

bool isPrime(int n)
{
	if (n == 2 || n == 3 || n == 5 || n == 7)
		return 1;
	if ( n%2 == 0 || n%3 == 0 || n%5 == 0 || n%7 == 0)
		return 0;
	int count = 0;
	for (int i = 2; i < n/2 + 1; i ++)
	{
		if (n % i == 0)
			count ++;
	}
	if (count > 0)
		return 0;
	else
		return 1;
}


int main()
{
	printf("Number of processors available = %d\n",omp_get_num_procs());
	int num = 0;
	int N = 5000;//131072
		
	printf("Parallel code\n");
	int j = 2;
	double time_spent = 0.0;
	clock_t begin_1 = clock();
	num = 0;
	#pragma omp parallel
	#pragma omp for
		for(int i = 2;i < N; i ++)
		{
			if (isPrime(i))
			{
				// sleep(0.1);
				#pragma omp atomic
				num++;
				// printf("%d ",i);
			}
		}
	printf("\n%d\n",num);
	clock_t end_1 = clock();
	time_spent += (double)(end_1 - begin_1) / CLOCKS_PER_SEC * 1000;
	printf("Time elpased is %f milliseconds\n\n\n", time_spent);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	printf("Serial Code\n");
	num = 0;
	time_spent = 0.0;
	clock_t begin = clock();
	for (int i = 2;i <= N; i++) 
	{
		if (isPrime(i))
		{
			num++;
			// printf("%d ",i);
		}
	}
	printf("\n%d\n",num);
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC * 1000;
	printf("Time elpased is %f milliseconds\n\n\n", time_spent);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////

	return 0;
}