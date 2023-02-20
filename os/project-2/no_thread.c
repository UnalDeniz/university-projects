#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "statistical_funcs.h"
#include "util_funcs.h"

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

	gettimeofday(&tv, NULL);
	double calc_start_time = tv.tv_sec + 0.000001 * tv.tv_usec;

	min();
	max();
	range();
	mode();
	median();
	sum();
	a_mean();
	h_mean();
	s_deviation();
	interquartile_range();
	
	gettimeofday(&tv, NULL);
	double end_time = tv.tv_sec + 0.000001 * tv.tv_usec;
	print_all("output1.txt", end_time - calc_start_time);

	free(arr);
    
	return 0;
}

