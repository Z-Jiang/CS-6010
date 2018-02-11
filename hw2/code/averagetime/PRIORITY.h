#ifndef PRIORITY_h
#define PRIORITY_h

//define the node in priority queue.
typedef struct event {
    double event_time;
    int event_type;
    struct event * next;
}EVENT;

//define the priority queue.
typedef struct priority_queue{
    EVENT * head;
    int pq_size;    //counting the length of the priority queue.
}PRIORITY;

//initiate a priority queue.
PRIORITY * create_PRIORITY_QUEUE ();

//to add nodes(the events) to the priority queue with their values of event_time in an ascending order, hence the SMALLER the event_time is, the HIGHER their priority is.
void insert_event (PRIORITY * pq, double event_time, int event_type);

// output the nodes(the events) from the begining to the end (which is in the order of their priority) in the priority queue.
EVENT * pop_event (PRIORITY * pq);

//to free every allocated memory from the priority queue.
void delete_PRIORITY_QUEUE (PRIORITY * pq);


#endif /* PRIORITY_h */
