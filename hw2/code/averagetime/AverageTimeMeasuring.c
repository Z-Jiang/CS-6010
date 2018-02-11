#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "PRIORITY.h"
#include "random.h"


 
 int main(){
     int a, b, N;
     double long c;
     srand((unsigned)time(NULL));
    PRIORITY *pq = create_PRIORITY_QUEUE();    //initiate the priority queue to contain N events.
     printf("Please indicate the amount of events you want to insert into the priority queue:\n");
     scanf("%d", &N);
 
     for(a = 0; a < N; a++)                     //insert N events into the priority queue.
    insert_event(pq, urand(), 5);
 
     clock_t start, end;
     start = clock();
    for (b = 0; b < 100000; b++) {
        insert_event(pq, urand(), 5);
        pop_event(pq);
    }
     end = clock();
     c = (double)(end - start)/ (100000*CLOCKS_PER_SEC);
     printf("The average time for one iteration of the loop is %Lfs\n", c);
     void delete_PRIORITY_QUEUE (PRIORITY * pq);
     return 0;
 }
 



























