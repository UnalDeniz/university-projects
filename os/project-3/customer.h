struct Customer{
	int id;
	int sleepTime;
	int vendingID;
	char company[7];
	int amount;
};

// This variable will be equal to 1 when all prepayments are done.
int g_customerDone = 0;
// Holds all customer struct instances, array index = id - 1.
struct Customer g_customerArr[300];
// Function that will be called inside the customer threads.
void *Prepay(void *customerID);

