#include <math.h>

extern int *arr;
extern int count;
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

void* min(){

	min_value = arr[0];
}

void* max(){

	max_value = arr[count-1];
}

void* range(){

	range_value = arr[count-1] - arr[0];

}

void* mode(){

	int mode;
	int mode_count = 0;
	int curr = arr[0];
	int curr_count = 0;

	for(int i = 0; i < count; i++){

		if(arr[i] != curr){
			
			curr_count = 1;
			curr = arr[i];

		} else {

			curr_count++;

			if(curr_count > mode_count){

				mode = curr;
				mode_count = curr_count;
			}
		}
	}

	mode_value =  mode;
}

void* median(){

	if(count % 2 == 1){
		median_value = arr[(count-1)/2];
	} else {
		double median = (double) (arr[count/2] + arr[(count/2)-1]) / 2;
		median_value = median; 
	}
}

void* sum(){

	int tot  = 0;

	for(int i = 0; i < count; i++)
		tot += arr[i];

	sum_value = tot;
}

int return_sum(){ //instead of saving the result, returns it to be used in other functions

	int tot  = 0;

	for(int i = 0; i < count; i++)
		tot += arr[i];

	return tot;
}

void* a_mean(){

	a_mean_value = (double) return_sum() / count;

}

double return_a_mean(){ //instead of saving the result, returns it to be used in other functions

	return (double) return_sum() / count;

}


void* h_mean(){

	double reciprocal_sum = 0;

	for(int i = 0; i < count; i++){
		reciprocal_sum += (double) 1 / arr[i];
	}
	
	h_mean_value = count / reciprocal_sum;
}

void* s_deviation(){
	
	int mean = return_a_mean();

	double deviation = 0;

	for(int i = 0; i < count; i++){
		deviation += pow((arr[i] - mean), 2);
	}
	
	deviation = deviation / (count - 1);
	deviation = sqrt(deviation);

	s_deviation_value = deviation;
}

void* interquartile_range(){
	
	double first_q;
	double third_q;

	if(count % 4 == 0){
		first_q = (double)(arr[count/4] + arr[(count/4)-1]) / 2;
		third_q = (double)(arr[(count/4) + (count/2)] + arr[(count/4) + (count/2) - 1]) / 2;
	} else if(count % 2 == 0){
		first_q = arr[((count/2)-1)/2];
		third_q = arr[(((count/2)-1)/2) + (count/2)];
	} else if( (count-1) % 4 == 0){
		first_q = (double)(arr[(count-1)/4] + arr[((count-1)/4)-1]) / 2;
		third_q = (double)(arr[((count-1)/4) + ((count-1)/2)] + arr[((count-1)/4) + ((count-1)/2) + 1]) / 2;
	} else {
		first_q = arr[(((count-1)/2)-1)/2];
		third_q = arr[(count-1)/2 + (((count-1)/2)-1)/2 + 1];
	}
	
	interquartile_range_value = third_q - first_q;
}
