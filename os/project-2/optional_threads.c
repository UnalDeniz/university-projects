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

	int thread_count;

	if(argv[2] != NULL){
		thread_count = str2int(argv[2]);

		if(thread_count > 10 || thread_count < 1){
			printf("The thread count could only be between 1 and 10. Please try again with a possible thread count.\n");
			return -1;
		}

		printf("thread count is %d\n", thread_count);

	} else {

		thread_count = 10;

		printf("\nThread count is set to 10 by default, to select the number of threads add it as a argument.\n");
		printf("The syntax is as the following: \".optional_threads.c <array-size> <number-of-threads>\"\n");
		printf("Number of threads could be any number between 1 and 10. \n\n");
	}

	generate_arr(&arr, count, (int)start_time); // generates array and sorts it (start time is used as a seed)

	void* (*fun_ptr[10])();
	fun_ptr[0] = &min;
	fun_ptr[1] = &max;
	fun_ptr[2] = &range;
	fun_ptr[3] = &mode;
	fun_ptr[4] = &median;
	fun_ptr[5] = &sum;
	fun_ptr[6] = &a_mean;
	fun_ptr[7] = &h_mean;
	fun_ptr[8] = &s_deviation;
	fun_ptr[9] = &interquartile_range;

	pthread_t threads[thread_count];

    struct fun_list execution_list[thread_count]; //struct holds number of functions to be executed and array of them

    int func_count = 10 / thread_count;
    
    for(int i = 0; i < 10 - (thread_count * func_count); i++){
        execution_list[i].list_size = func_count + 1;

        for(int j = 0; j < func_count + 1; j++){ //to distribute the functions if the thread count doesnt divide 10 some of them executes 1 more than others
            execution_list[i].func_ptr[j] = fun_ptr[i * (func_count+1) + j];
        }
    }

    for(int i = 10 - (thread_count * func_count); i < thread_count; i++){
        execution_list[i].list_size = func_count;
        for(int j = 0; j < func_count; j++){
            execution_list[i].func_ptr[j] = fun_ptr[9 - (func_count - 1 -j) - (func_count * (thread_count -1 -i))];
        }
    }


	gettimeofday(&tv, NULL);
	double calc_start_time = tv.tv_sec + 0.000001 * tv.tv_usec;

	/*for(int i = 0; i < count; i++)
		printf("arr[%d] is:\t%d\n", i, arr[i]);*/

	for(int i = 0; i < thread_count; i++){
		pthread_create(&threads[i], NULL, execute, &execution_list[i]);
	}
	
	for(int i = 0; i < thread_count; i++){
		pthread_join(threads[i], NULL);
	}

	gettimeofday(&tv, NULL);
	double end_time = tv.tv_sec + 0.000001 * tv.tv_usec;
	print_all("output4.txt", end_time - calc_start_time);

	free(arr);

	return 0;
}

