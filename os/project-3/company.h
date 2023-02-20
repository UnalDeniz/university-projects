#include <pthread.h>

/*
 * There is a lock for each company in order to
 * prevent simultaneous accesses to variables 
 * resulting in race conditions.
 */
pthread_mutex_t g_lockBob;
pthread_mutex_t g_lockDave;
pthread_mutex_t g_lockKevin;
pthread_mutex_t g_lockOtto;
pthread_mutex_t g_lockStuart;

/*
 * Variables below hold the total amount of
 * prepayment that is done to their 
 * correspondging company so far.
 */
int g_totalBob = 0;
int g_totalDave = 0;
int g_totalKevin = 0;
int g_totalOtto = 0;
int g_totalStuart = 0;
