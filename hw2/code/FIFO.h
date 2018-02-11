#ifndef FIFO_h
#define FIFO_h

//define the node in FIFO queue.
typedef struct part {
    double service_time;
    double enter_time;
    struct part * next;
}PART;

//define the FIFO queue.
typedef struct FIFO {
    PART * head;
    PART * rear;
    int counter;  //counting the length of the FIFO queue.
}FIFO;

//initiate a FIFO queue.
FIFO * create_FIFO ();

//to add nodes(the parts) into the FIFO queue.
void add_part (double service_time, double interarrival, FIFO * queue);

//output the nodes(the parts) from the begining to the end (which is based on the "first in first out" rule) in the FIFO queue.
PART * pop_part (FIFO * queue);

//to free every allocated memory from the FIFO queue.
void delete_FIFO (FIFO * queue);


#endif /* FIFO_h */
