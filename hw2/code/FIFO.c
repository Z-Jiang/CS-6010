#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "FIFO.h"
#include "random.h"

extern int partCount;

//initiate a FIFO queue.
FIFO * create_FIFO () {
    FIFO * queue = (FIFO *) malloc(sizeof(struct FIFO));
    if(queue == NULL){
        printf("Fatal Error: Out of memory!\n");
        exit(1);
    }
    queue->head = NULL;
    queue->rear = NULL;
    queue->counter = 0;
    return queue;
}

//to add nodes(the parts) into the FIFO queue.
void add_part (double service_time, double enter_time, FIFO * queue){
    PART * current = (PART *) malloc(sizeof(struct part));
    if(current == NULL){
        printf("Fatal Error: Out of memory!\n");
        exit(1);
    }
    current->service_time = service_time;
    current->enter_time = enter_time;
    current->next = NULL;
    if ( queue->counter == 0)
        queue->head = queue->rear = current;
    else {
        queue->rear->next = current;
        queue->rear = current;
    }
    queue->counter++;
}

//output the nodes(the parts) from the begining to the end (which is based on the "first in first out" rule) in the FIFO queue.
PART * pop_part (FIFO * queue){
    if (queue->counter == 0) {
        return NULL;
    } else {
        queue->counter--;
        PART *part = queue->head;
        queue->head = queue->head->next;
        return part;
    }

}


//to free every allocated memory from the FIFO queue.
void delete_FIFO (FIFO * queue) {
    PART * current = queue->head;
    if (queue->head == NULL)
        return;
    else if (queue->head == queue->rear)
        queue->head = queue->rear = NULL;
    else
        queue->head =queue->head->next;
    free (current);
    free(queue);
}

