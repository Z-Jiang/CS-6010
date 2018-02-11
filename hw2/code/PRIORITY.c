#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "PRIORITY.h"
#include "random.h"

extern int partCount;

//initiate a priority queue.
PRIORITY * create_PRIORITY_QUEUE () {
    PRIORITY * pq = (PRIORITY *) malloc(sizeof(struct priority_queue));
    if(pq == NULL){
        printf("Fatal Error: Out of memory!\n");
        exit(1);
    }
    pq->head = NULL;
    pq->pq_size = 0;
    return pq;
}

//to add nodes(the events) to the priority queue with their values of event_time in an ascending order, hence the SMALLER the event_time is, the HIGHER their priority is.
void insert_event (PRIORITY * pq, double event_time, int event_type) {
    if (pq == NULL){
        printf("No memory for this queue!");
        return;
    }
    EVENT * new = (EVENT *) malloc(sizeof(struct event));
    if(new == NULL){
        printf("Fatal Error: Out of memory!\n");
        exit(1);
    }
    new->event_time = event_time;
    new->event_type = event_type;
    new->next = NULL;
    
    if (pq->head == NULL) {
        pq->head = new;
        pq->pq_size++;
        return;
    } else if (pq->head->event_time > new->event_time) {
        new->next = pq->head;
        pq->head = new;
        pq->pq_size++;
        return;
    }
    
    EVENT *former = pq->head;
    EVENT *later = pq->head->next;
    while (later != NULL) {
        if (later->event_time > new->event_time) {
            new->next = later;
            former->next = new;
            pq->pq_size++;
            return;
        }
        former = former->next;
        later = later->next;
    }
    
    former->next = new;
    pq->pq_size++;

}


// output the nodes(the events) from the begining to the end (which is in the order of their priority) in the priority queue.
EVENT * pop_event (PRIORITY * pq) {
    EVENT * new = pq->head;
    if (pq->head == NULL)
        return new;
    else
        pq->head = pq->head->next;
    pq->pq_size--;
    return new;
}


//to free every allocated memory from the priority queue.
void delete_PRIORITY_QUEUE (PRIORITY * pq) {
    EVENT * new = pq->head;
    if (pq->head == NULL)
        free (pq);
    else
        pq->head = pq->head->next;
    free (new);
    free (pq);
}


