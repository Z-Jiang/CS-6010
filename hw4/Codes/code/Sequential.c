#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define LEN 50

int N;

void swap (int *a, int *b);
int partition (int array[], int p, int r);
void quicksort (int array[], int p, int r);
void output(char *filename, int array[], double long time);




int main(int argc, char * argv[]) {
    
    srand((unsigned)time(NULL));

    if(argc != 3){
        fprintf(stderr, "Usage: Number of elements, name of the output file\n");
        exit(EXIT_FAILURE);
    }
    
    N = atoi(argv[1]);
    double long time;
    int array[N];
    int i;
    clock_t start, end;

//Initialize the array with N randomly generated numbers in a random ordered fashion.
    for ( i = 0; i < N; i++) {
        array[i] = rand() % (N *10);
    }


/*
//Initialize the array with N numbers in a decreasing order with a decrement of 1, simulating the WORST case.

    for (i = 0; i < N; i++) {
        array[i] = N-i;
    }
    array[N-1] = array[N/2];
*/

    start = clock();                // start recording the execution time of sequential quicksort.
    quicksort (array, 0, N-1);
    end = clock();

    time = (double)(end - start) / (CLOCKS_PER_SEC);

    printf("The running time of the quick-sort algorithm in sequential program is: %Lfs\n", time);
    output(argv[2], array, time);

    return 0;
}












//recursively quicksort the array
void quicksort (int array[], int p, int r){
    int q;
    if (p < r) {
        q = partition(array, p, r);
        quicksort(array, p, q - 1);
        quicksort(array, q + 1, r);
    }
}

//exchange the elements' position where necessary and return the index of the pivot element to next quicksort function.
int partition (int array[], int p, int r){
    int x, i, j;
    x = array[r];
    i = p -1;
    for (j = p; j < r; j++) {
        if (array[j] <= x){
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i +1], &array[r]);
    return (i + 1);
}


//generate the output file.
void output(char *filename, int array[], double long time){
    FILE* fp;
    int i;
    char name[LEN];
    strcpy(name,filename);
    strcat(name, ".txt");
    if((fp = fopen(name, "w")) == NULL){
        fprintf(stderr, "Error in opening the output file\n");
        exit(EXIT_FAILURE);
    }
       
        fprintf(fp, "The execution time for sorting %d numbers with quicksort method utilizing sequential algorithm is: %Lfs\n", N, time);
        for (i = 0; i < N; i++){
            fprintf(fp, "%d\n", array[i]);
        }
        fprintf(fp, "\n");
    
    if(fclose(fp) != 0){
        fprintf(stderr, "Error in closing topology file.\n");
        exit(EXIT_FAILURE);
    }
}


void swap (int* c, int* d){
    int e;
    e = *c;
    *c = *d;
    *d = e;
}


