#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "customer.h"
#include "vending-machine.h"
#include "company.h"

pthread_mutex_t file_lock;
FILE *g_output;

int main(int argc, char** argv){
	/*
	 * Tests if the number of arguments that are given to program is correct.
	 * If it is not, throws an error and exits.
	 */
	if(argc != 2){
		fprintf(stderr, "Please give the program arguments correctly!\n");
		exit(-1);	
	}

	char inputName[256];
	strncpy(inputName, argv[1], sizeof(inputName));

	FILE *input;
	input = fopen(inputName, "r");
	
	// Reads the first line and holds the number as an integer.
	char buffer[256];
	fgets(buffer, 256, input);
	int customerCount = atoi(buffer);
	
	/*
	 * Reads the rest of the file and sets the variables of 
	 * the struct instances in the g_customerArr accordingly.
	 */
	for(int i = 0; i < customerCount; i++){
		struct Customer nextCustomer;
		nextCustomer.id = i;

		fgets(buffer, 256, input);

		char *token;
		token = strtok(buffer, ",");
		nextCustomer.sleepTime = atoi(token);
		
		token = strtok(NULL, ",");
		nextCustomer.vendingID = atoi(token)-1;

		token = strtok(NULL, ",");
		strncpy(nextCustomer.company, token, sizeof(nextCustomer.company));

		token = strtok(NULL, ",");
		nextCustomer.amount = atoi(token);

		g_customerArr[i] = nextCustomer;
	}

	fclose(input);

	/*
	 * Takes the address to the input file and removes the 
	 * directories and file extension parts to get the
	 * exact name of the file.
	 */
	char *token;
	char* rest;
	token = strtok(inputName, "/");
	rest = strtok(NULL, ".");

	if(rest != NULL){ // Continues removeing directories until none left.
		while(rest != NULL){
			token = strtok(rest, "/");
			rest = strtok(NULL, ".");
		}
	} else { // If file is in the working directory only removes file extension.
		token = strtok(token, ".");
	}

	char outputName[256];
	strncpy(outputName, token, sizeof(outputName));
	strcat(outputName, "_log.txt"); // Formats the name to the desired format.
	g_output = fopen(outputName, "w");

	/*
	 * Initializes the vendingMachine instances,
	 * by setting their id and initializing requested 
	 * variable to default value.
	 */
	for(int i = 0; i < 10; i++){
		g_vendingArr[i].id = i;
		g_vendingArr[i].requested = 0;
	}

	pthread_t vendingThreads[10];
	int indexes[customerCount];

	for(int i = 0; i < customerCount; i++){
		indexes[i] = i;
	}

	for(int i = 0; i < 10; i++){
		pthread_create(&vendingThreads[i], NULL, Vending, &indexes[i]);
	}

	pthread_t customerThreads[customerCount];

	for(int i = 0; i < customerCount; i++){
		pthread_create(&customerThreads[i], NULL, Prepay, &indexes[i]);
	}

	for(int i = 0; i < customerCount; i++){
		pthread_join(customerThreads[i], NULL);
	}

	/*
	 * In my implementation customers exits without waiting for
	 * vending machine to finish their prepayment.
	 * This part is to ensure that last customer's prepayment is finished.
	 */
	int requestDone = 1;

	while(requestDone){
		requestDone = 0;
		for(int i = 0; i < 10; i++){
			if(g_vendingArr[i].requested == 1){
				requestDone = 1;
				break;
			}
		}
	}

	/* 
	 * If the prepayment of the last customer is finished,
	 * vending machines can exit.
	 */
	g_customerDone = 1;

	for(int i = 0; i < 10; i++){
		pthread_join(vendingThreads[i], NULL);
	}

	fprintf(g_output, "All prepayments are completed.\n");
	fprintf(g_output, "Kevin: %dTL\n", g_totalKevin);
	fprintf(g_output, "Bob: %dTL\n", g_totalBob);
	fprintf(g_output, "Stuart: %dTL\n", g_totalStuart);
	fprintf(g_output, "Otto: %dTL\n", g_totalOtto);
	fprintf(g_output, "Dave: %dTL\n", g_totalDave);

	fclose(g_output);

	return 0;
}

void *Vending(void *vendingID){
	struct VendingMachine *machine = &g_vendingArr[*(int*)vendingID];

	/*
	 * Vending machines loops until all customers' prepayment are done.
	 * When there is a prepayment request send by a customer,
	 * they complete the request using the data that is transmitted 
	 * by customer, and set themselves as not requested once again.
	 */
	while(!g_customerDone){
		if(machine->requested == 1){
			if(strcmp(machine->company, "Bob") == 0){
				pthread_mutex_lock(&g_lockBob);
				g_totalBob += machine->amount;
				pthread_mutex_unlock(&g_lockBob);

			}  else if(strcmp(machine->company, "Dave") == 0){
				pthread_mutex_lock(&g_lockDave);
				g_totalDave += machine->amount;
				pthread_mutex_unlock(&g_lockDave);

			} else if(strcmp(machine->company, "Kevin") == 0){
				pthread_mutex_lock(&g_lockKevin);
				g_totalKevin += machine->amount;
				pthread_mutex_unlock(&g_lockKevin);

			} else if(strcmp(machine->company, "Otto") == 0){
				pthread_mutex_lock(&g_lockOtto);
				g_totalOtto += machine->amount;
				pthread_mutex_unlock(&g_lockOtto);

			} else{
				pthread_mutex_lock(&g_lockStuart);
				g_totalStuart += machine->amount;
				pthread_mutex_unlock(&g_lockStuart);

			}

			/*
			 * Printing to file statement is inside a lock to prevent
			 * multiple threads from writing at the same time 
			 * and corrupting the output.
			 */
			pthread_mutex_lock(&file_lock);
			fprintf(g_output, "Customer%d,%dTL,%s\n", machine->customerID+1,
					machine->amount, machine->company);
			pthread_mutex_unlock(&file_lock);
			machine->requested = 0; // The request is done so flag is unset.
			// Prepayment is complete so next customer can request a new prepayment.
			pthread_mutex_unlock(&g_vendingLocks[machine->id]);
		}
	}
}

void *Prepay(void *customerID){
	struct Customer *customer = &g_customerArr[*(int*)customerID];
	usleep(customer->sleepTime * 1000);
	/*
	 * Sets a lock to prevent other customers requesting 
	 * prepayment without the current one is complete.
	 */
	pthread_mutex_lock(&g_vendingLocks[customer->vendingID]);
	
	struct VendingMachine *machine = &g_vendingArr[customer->vendingID];
	/*
	 * Sets the necessary data so that vending machine
	 * can process the prepayment.
	 */
	machine->customerID = customer->id;
	strncpy(machine->company, customer->company, sizeof(machine->company));
	machine->amount = customer->amount;
  // Sets a flag to let vending machine know there is a prepayment to process.
	machine->requested = 1; 
}

