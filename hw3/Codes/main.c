#include "Graph_Generation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int N;

int main(int argc, char * argv[]) {
    
    srand((unsigned)time(NULL));
    
    if(argc != 5){
        fprintf(stderr, "Usage: node's number, name of topology file, '-h' name of histogram file \n");
        exit(EXIT_FAILURE);
    }
    
    N = atoi(argv[1]);
    
    GRAPH* graph = create_graph (N);
    
    initial_graph (graph);
    
    append_nodes (graph);
    
    output_topology(argv[2], graph);
    
    append_source (graph);
    
//---------------------------Below is the construction of histogram graph--------------------------------------//

    
    HISTOGRAM* histogram = create_histogram (graph);
    
    append_nodes_into_hist (histogram, graph);
    
    output_histogram(argv[4], histogram, graph);
    
    free_memory(histogram, graph);
    
    return 0;
}




