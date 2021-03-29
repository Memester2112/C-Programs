#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include<math.h>
#include<unistd.h>

double dist(double x, double y)
{
	return sqrt(x*x + y*y);
}

int main()
{
	srand(time(NULL));//seeding with time = 0
	double pi = M_PI;
	
	double x ;
	double y ;
	printf("Number of processors available = %d\n\n\n",omp_get_num_procs());
	
	double my_pi = 0;
	long long square = 0;
	long long circle = 0;
	double threshold = 1e-2;
	double time_spent = 0.0;
	
	printf("Serial Code \n");
	clock_t begin_1 = clock();
	
	while(abs(pi - my_pi) > threshold)
	{
		x = 1.0*(rand())/RAND_MAX;
		y = 1.0*(rand())/RAND_MAX;
		// printf("%f, %f \n",x,y);
		square++;
		if (dist(x,y)<=1.0)
		{
			circle++;
		}
		my_pi = 4*1.0*circle/square;
		// printf("circle = %d, square = %d PI = %f\n",circle,square,my_pi);

	}
	
	clock_t end_1 = clock();
	time_spent += (double)(end_1 - begin_1) / CLOCKS_PER_SEC * 1000;
	printf("Time elpased is %f milliseconds\n", time_spent);
	
	printf("%f\n\n\n",my_pi);
	
	sleep(1);
	
	printf("Parallel code\n");
	
	time_spent = 0;
	square = 0;
	circle = 0;
	my_pi = 0.0;
	int threadNums = 12;
	clock_t begin_2 = clock();
	int cir[threadNums];
	for (int i = 0; i < threadNums; i++)
	{
		cir[i] = 0;
	}
	
	// #pragma omp parallel
	while(abs(pi-my_pi) > threshold)
	{
		#pragma omp for
			for (int i = 0; i < threadNums; i++)
			{
				srand(time(0)*rand());
				x = 1.0*(rand())/RAND_MAX;
				y = 1.0*(rand())/RAND_MAX;
				if(dist(x,y)<=1.0)
					cir[i]++;
				// printf("%f, %f TID = %d\n",x,y,i);
			}
		
		// printf("\nOutside for loop in TID = %d\n",omp_get_thread_num());
		square += threadNums;
		circle = 0;
		for (int i = 0; i < threadNums; i++)
			circle += cir[i];
		my_pi = 4*1.0*circle/square;
		// printf("\nSleeping for 5 seconds circle = %d square = %d my_pi = %f\n",circle,square,my_pi);
		// sleep(1);
	}
	
	clock_t end_2 = clock();
	time_spent += (double)(end_2 - begin_2) / CLOCKS_PER_SEC * 1000;
	printf("Time elpased is %f milliseconds\n", time_spent);
	
	printf("%f\n",my_pi);
	
	return 0;
}