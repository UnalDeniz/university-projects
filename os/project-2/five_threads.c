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

    struct fun_list execution_list[5]; //struct holds number of functions to be executed and array of them

    for(int i = 0; i < 5; i++){
        execution_list[i].list_size = 2;
    }

    execution_list[0].func_ptr[0] = &min;
    execution_list[0].func_ptr[1] = &max;
    execution_list[1].func_ptr[0] = &range;
    execution_list[1].func_ptr[1] = &mode;
    execution_list[2].func_ptr[0] = &median;
    execution_list[2].func_ptr[1] = &sum;
    execution_list[3].func_ptr[0] = &a_mean;
    execution_list[3].func_ptr[1] = &h_mean;
    execution_list[4].func_ptr[0] = &s_deviation;
    execution_list[4].func_ptr[1] = &interquartile_range;

	gettimeofday(&tv, NULL);
	double calc_start_time = tv.tv_sec + 0.000001 * tv.tv_usec;
    
	pthread_create(&thread_0, NULL, execute, &execution_list[0]);
	pthread_create(&thread_1, NULL, execute, &execution_list[1]);
	pthread_create(&thread_2, NULL, execute, &execution_list[2]);
	pthread_create(&thread_3, NULL, execute, &execution_list[3]);
	pthread_create(&thread_4, NULL, execute, &execution_list[4]);

	pthread_join(thread_0, NULL);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	pthread_join(thread_3, NULL);
	pthread_join(thread_4, NULL);

	gettimeofday(&tv, NULL);
	double end_time = tv.tv_sec + 0.000001 * tv.tv_usec;
    print_all("output2.txt", end_time - calc_start_time);

	free(arr);

	return 0;
}

