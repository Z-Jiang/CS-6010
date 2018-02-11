#include <stdio.h>
#include "Engine.h"
#include <stdlib.h>
#include <time.h>

// define global variables
double waitingTime = 0;
double totalServiceTime = 0;
int customer_count = 0;
int partCount = 0;

//run the engine and start simulation
int main(void) {
    srand((unsigned)time(NULL));
    Engine *simulator = initialEngine();
    run(simulator);
    printf("Total waiting time is %f\n", waitingTime);
    printf("Average waiting time is %f\n", waitingTime/customer_count);
    printf("Total time in the system %f\n", waitingTime + totalServiceTime);
    printf("Average time in the system %f\n",(waitingTime+totalServiceTime)/customer_count);
    return 0;
}

