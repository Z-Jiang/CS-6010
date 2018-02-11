#include "Graph_Generation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LEN 50

extern int N;

//create a new node.
NODE * create_node (int ID){
    NODE* newnode = (NODE*) malloc(sizeof(NODE));
    if(newnode == NULL){
        printf("Fatal Error: Out of memory!\n");
        exit(1);
    }
    newnode->ID = ID;
    newnode->next = NULL;
    return newnode;
}

//create a graph.
GRAPH * create_graph (int N){
    int i;
    GRAPH* newgraph = (GRAPH*) malloc(sizeof(GRAPH));
    if(newgraph == NULL){
        printf("Fatal Error: Out of memory!\n");
        exit(1);
    }
    newgraph->listarray = (NODE_LIST*) malloc(sizeof(NODE_LIST) * N);
    if(newgraph->listarray == NULL){
        printf("Fatal Error: Out of memory!\n");
        exit(1);
    }
    for (i = 0; i < N; i++) {
        newgraph->listarray[i].head = NULL;
        newgraph->listarray[i].degree = 0;
        newgraph->num_list = 0;
    }
    return newgraph;
}

//initialize a fully connected topology with 3 nodes in the created graph.
void initial_graph (GRAPH* graph){
    int i, j;                        //i refers to the source nodes, while j refers to the destination nodes.
    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 3; j++) {
            NODE* newnode = create_node(j);
            newnode->next = graph->listarray[i].head;
            graph->listarray[i].head = newnode;
            graph->listarray[i].degree += 1;
            graph->num_list +=1;
            
            newnode = create_node(i);
            newnode->next = graph->listarray[j].head;
            graph->listarray[j].head = newnode;
            graph->listarray[j].degree += 1;
        }
    }
}

//append a newly created node into the graph.
void append_nodes (GRAPH* graph){
    int i;
    for (i = 3; i < N; i++) {
        int j = select_list(graph);
        NODE* newnode = create_node(j);
        newnode->next = graph->listarray[i].head;
        graph->listarray[i].head = newnode;
        graph->listarray[i].degree += 1;
        graph->num_list +=1;
        
        newnode = create_node(i);
        newnode->next = graph->listarray[j].head;
        graph->listarray[j].head = newnode;
        graph->listarray[j].degree += 1;
    }
}

//this function is just for the convenience of outputing histogram, it adds the source node at the beginning of every node list of the created graph, it MUST be called AFTER outputing the topology.
void append_source (GRAPH* graph){
    int i;
    for (i = 0; i < N; i++) {
        NODE* source = create_node(i);
        source->next = graph->listarray[i].head;
        graph->listarray[i].head = source;
        
    }
}

//select a node list according to preferential attachment principle.
int select_list(GRAPH* graph){
    int i, b;
    int random = 0;
    int D = 0;
    for(i = 0; i < graph->num_list; i++){
        D += graph->listarray[i].degree;
    }
    random = (rand() % D + 1);
    b = random;
    for (i = 0; random > 0; i++){
        random = random - graph->listarray[i].degree;
    }
    return i-1;
}






//---------------------------Below is the construction of histogram graph--------------------------------------//







//find the maximum degree of the nodes.
int find_max_degree (GRAPH* graph){
    int i;
    int max = 0;
    for( i =0; i < N; i++){
        if (graph->listarray[i].degree > max)
            max = graph->listarray[i].degree;
    }
    return max;
}

//create a histogram.
HISTOGRAM * create_histogram (GRAPH* graph){
    int i;
    int max = find_max_degree(graph);
    HISTOGRAM* newhist = (HISTOGRAM*) malloc(sizeof(HISTOGRAM));
    if(newhist == NULL){
        printf("Fatal Error: Out of memory!\n");
        exit(1);
    }
    newhist->orderedarray = (DEGREE_LIST*) malloc(sizeof(DEGREE_LIST) * max);
    if(newhist->orderedarray == NULL){
        printf("Fatal Error: Out of memory!\n");
        exit(1);
    }
    for (i = 0; i < max; i++) {
        newhist->orderedarray[i].head = NULL;
        newhist->orderedarray[i].degree = i + 1;
        newhist->orderedarray[i].total = 0;
    }
    return newhist;
}

//append the created nodes of each node_list into the histogram according to the list's degree.
void append_nodes_into_hist (HISTOGRAM* histogram, GRAPH* graph){
    int i, j;
    int max = find_max_degree(graph);
    for (i = 1; i <= max; i++) {
        for(j = 0; j < N; j++){
            if ( graph->listarray[j].degree == i){
                histogram->orderedarray[i-1].total += 1;
            }
        }
    }
    
    for (i = 1; i <= max; i++) {
        for(j = 0; j < N; j++){
            if ( graph->listarray[j].degree == i){
                graph->listarray[j].head->next = histogram->orderedarray[i-1].head;
                histogram->orderedarray[i-1].head = graph->listarray[j].head;
            }
        }
    }
}

//generate the topology file.
void output_topology(char *filename, GRAPH* graph){
    FILE* fp;
    int i;
    char name[LEN];
    strcpy(name,filename);
    strcat(name, ".csv");
    if((fp = fopen(name, "w")) == NULL){
        fprintf(stderr, "Error in opening topology file\n");
        exit(EXIT_FAILURE);
    }
    
    for (i = 0; i < N; i++) {
        NODE* node = graph->listarray[i].head;
        fprintf(fp, "%d,%d,", i, graph->listarray[i].degree);
        while(node){
            fprintf(fp, "%d,", node->ID);
            node = node->next;
        }
        fprintf(fp, "\n");
    }
    if(fclose(fp) != 0){
        fprintf(stderr, "Error in closing topology file.\n");
        exit(EXIT_FAILURE);
    }
}

//generate the histogram file.
void output_histogram(char *filename, HISTOGRAM* histogram, GRAPH* graph){
    FILE* fp;
    int i;
    int max = find_max_degree(graph);
    char name[LEN];
    strcpy(name,filename);
    strcat(name, ".csv");
    if((fp = fopen(name, "w")) == NULL){
        fprintf(stderr, "Error in opening histogram file\n");
        exit(EXIT_FAILURE);
    }
    
    for (i = 0; i < max; i++) {
        NODE* node = histogram->orderedarray[i].head;
        fprintf(fp,"%d,%d,", histogram->orderedarray[i].degree, histogram->orderedarray[i].total);
        while(node){
            fprintf(fp, "%d,", node->ID);
            node = node->next;
        }
        fprintf(fp, "\n");
    }
    if(fclose(fp) != 0){
        fprintf(stderr, "Error in closing histogram file.\n");
        exit(EXIT_FAILURE);
    }
}

//free all the allocated memory to avoid memory leak.
void free_memory(HISTOGRAM* histogram, GRAPH* graph){
    free(histogram);
    free(histogram->orderedarray);
    free(graph);
    free(graph->listarray);
}
