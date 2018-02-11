#ifndef Graph_Generation_h
#define Graph_Generation_h

#include <stdio.h>


extern int N;

typedef struct node{
    int ID;
    struct node* next;
}NODE;

typedef struct node_list{
    int degree;
    NODE* head;
}NODE_LIST;

typedef struct graph{
    int num_list;
    NODE_LIST* listarray;
}GRAPH;

typedef struct degree_list{
    int degree;
    int total;
    NODE* head;
}DEGREE_LIST;

typedef struct histogram{
    DEGREE_LIST* orderedarray;
}HISTOGRAM;

//create a new node
NODE * create_node (int ID);

//create a graph
GRAPH * create_graph (int N);

//initialize a fully connected topology with 3 nodes in the created graph.
void initial_graph (GRAPH* graph);

//append a newly created node into the graph.
void append_nodes (GRAPH* graph);

//this function is just for the convenience of outputing histogram, it adds the source node at the beginning of every node list of the created graph, it MUST be called AFTER outputing the topology.
void append_source (GRAPH* graph);

//select a node list according to preferential attachment principle.
int select_list(GRAPH* graph);

//find the maximum degree of the nodes.
int find_max_degree (GRAPH* graph);

//create a histogram.
HISTOGRAM * create_histogram (GRAPH* graph);

//append the created nodes of each node_list into the histogram according to the list's degree.
void append_nodes_into_hist (HISTOGRAM* histogram, GRAPH* graph);

//generate the topology file.
void output_topology(char *filename, GRAPH* graph);

//generate the histogram file.
void output_histogram(char *filename, HISTOGRAM* histogram, GRAPH* graph);

//free all the allocated memory to avoid
void free_memory(HISTOGRAM* histogram, GRAPH* graph);

#endif /* Graph_Generation_h */
