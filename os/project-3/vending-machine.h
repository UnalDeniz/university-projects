#include <pthread.h>

struct VendingMachine{
	int id;
	int customerID;
	char company[7];
	int amount;
	int requested;
};

/*
 * There is a lock for each vending machine in order to
 * prevent different customers requesting prepayment 
 * from same vending machine at the same time.
 */
pthread_mutex_t g_vendingLocks[10];
// Holds all vending machine instances, array index = id - 1.
struct VendingMachine g_vendingArr[10];
// Function that will be called inside the vending machine threads.
void *Vending(void *vendingID);

