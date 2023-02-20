#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "statistical_funcs.h"
#include "util_funcs.h"
#include <pthread.h>

int *arr;
int count;

int main(int argc, char **argv){

	struct timeval tv;

	gettimeofday(&tv, NULL);
	double start_time = tv.tv_sec + 0.000001 * tv.tv_usec;

	count = str2int(argv[1]);

	if(count < 0){

		printf("Invalid N!\n");
		return -1;
	}

	generate_arr(&arr, count, (int)start_time); // generates array and sorts it (start time is used as a seed)

	/*for(int i = 0; i < count; i++)
		printf("arr[%d] is:\t%d\n", i, arr[i]);*/

	pthread_t thread_0;
	pthread_t thread_1;
	pthread_t thread_2;
	pthread_t thread_3;
	pthread_t thread_4;
	pthread_t thread_5;
	pthread_t thread_6;
	pthread_t thread_7;
	pthread_t thread_8;
	pthread_t thread_9;
		
	gettimeofday(&tv, NULL);
	double calc_start_time = tv.tv_sec + 0.000001 * tv.tv_usec;

	pthread_create(&thread_0, NULL, min, NULL);
	pthread_create(&thread_1, NULL, max, NULL);
	pthread_create(&thread_2, NULL, range, NULL);
	pthread_create(&thread_3, NULL, mode, NULL);
	pthread_create(&thread_4, NULL, median, NULL);
	pthread_create(&thread_5, NULL, sum, NULL);
	pthread_create(&thread_6, NULL, a_mean, NULL);
	pthread_create(&thread_7, NULL, h_mean, NULL);
	pthread_create(&thread_8, NULL, s_deviation, NULL);
	pthread_create(&thread_9, NULL, interquartile_range, NULL);

	pthread_join(thread_0, NULL);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	pthread_join(thread_3, NULL);
	pthread_join(thread_4, NULL);
	pthread_join(thread_5, NULL);
	pthread_join(thread_6, NULL);
	pthread_join(thread_7, NULL);
	pthread_join(thread_8, NULL);
	pthread_join(thread_9, NULL);

	gettimeofday(&tv, NULL);
	double end_time = tv.tv_sec + 0.000001 * tv.tv_usec;
	print_all("output3.txt", end_time - calc_start_time);

	free(arr);

	return 0;
}

