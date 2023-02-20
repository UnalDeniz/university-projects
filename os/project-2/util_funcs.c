#include <stdio.h>
#include <stdlib.h>
#include "util_funcs.h"

extern int min_value;
extern int max_value;
extern int range_value;
extern int mode_value;
extern double median_value;
extern int sum_value;
extern double a_mean_value;
extern double h_mean_value;
extern double s_deviation_value;
extern double interquartile_range_value;

int str2int(char *string){

	int result = 0;
	int negative = 0;

	for(int i = 0; string[i] != '\0'; i++){

		if(string[i] <= 57 && string[i] >= 48)
			result = result * 10 + string[i] - 48;

		else if(string[i] == 45) {

			if(i == 0)
				negative = 1;

			else {

				printf("The give input is not integer!\n");
				return -1;
			}

		} else {
			
			printf("The given input is not integer!\n");
			return -1;
		}

	}

	if(negative == 1)
		result = result * (-1);

	return result;
}

void quick_int_sort(int *arr, int low, int high){ // my implemenataion of the quick sort, not used in the project

	if(high > low){

		int pivot = low;
		int i = low;
		int j = high;
		int temp;

		while(i < j){

			while(i < j && arr[i] <= arr[pivot])
				i++;
			while(arr[j] > arr[pivot])
				j--;

			if(j > i){
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}

		temp = arr[pivot];
		arr[pivot] = arr[j];
		arr[j] = temp;

		quick_int_sort(arr, low, j-1);
		quick_int_sort(arr, j+1, high);
	}
}

int intCompare(const void *p1, const void *p2){ //comparison function that is used in qsort

    int int_a = * ( (int*) p1 );
    int int_b = * ( (int*) p2 );

    if(int_a == int_b)
	    return 0;
    else if(int_a < int_b)
	    return -1;
    else
	    return 1;
}

void generate_arr(int **arr_pointer, int size, int seed){ //creates array randomly and sorts it

	*arr_pointer = (int*)malloc(size * sizeof(int));

	srand(seed);

	for(int i = 0; i < size; i++){

		(*arr_pointer)[i] = (rand() % 9001) + 1000;
		//printf("arr[%d] is:\t%d\n", i, (*arr_pointer)[i]);

	}

	qsort(*arr_pointer, size, sizeof(int), intCompare);
}

void print_all(char filename[12], double time){

    FILE *output = fopen(filename, "w");
	fprintf(output, "%d\n", min_value);
	fprintf(output, "%d\n", max_value);
	fprintf(output, "%d\n", range_value);
	fprintf(output, "%d\n", mode_value);
	fprintf(output, "%.9g\n", median_value);
	fprintf(output, "%d\n", sum_value);
	fprintf(output, "%.9g\n", a_mean_value);
	fprintf(output, "%.9g\n", h_mean_value);
	fprintf(output, "%.9g\n", s_deviation_value);
	fprintf(output, "%.9g\n", interquartile_range_value);
    fprintf(output, "%.5f\n", time);
    fclose(output);
}

void *execute(void *args){ //takes a struct that has function pointer array as a member and executes the functions in that array
    
   struct fun_list *list_ptr = (struct fun_list*)args; 

   for(int i = 0; i < list_ptr->list_size; i++){
     (*(list_ptr->func_ptr[i]))();
   }
}
