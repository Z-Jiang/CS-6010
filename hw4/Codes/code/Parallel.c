#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include <sys/time.h>
#include <unistd.h>
#define NUM_THREADS 2
#define LEN 50

int N;

void swap (int *a, int *b);
int partition (int array[], int p, int r);
void quicksort_paralled (int array[], int p, int r);
void quicksort_sequential (int array[], int p, int r);
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
    struct timeval start, end;




//Initialize the array with N randomly generated numbers in a random ordered fashion.
    for ( i = 0; i < N; i++) {
            array[i] = rand() % (N*10);
        }

/*
//Initialize the array with N numbers in a decreasing order with a decrement of 1, simulating the WORST case.

    for (int i = 0; i < N; i++) {
        array[i] = N-i;
    }
    array[N-1] = array[N/2];
*/


    gettimeofday(&start, NULL);                 // start recording the execution time of paralleld quicksort.
    quicksort_paralled (array, 0, N-1);
    gettimeofday(&end, NULL);

    time =  ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;

    printf("The running time of the quick-sort algorithm in parallel program is: %Lfs\n", time);
    output(argv[2], array, time);

    return 0;
}









void quicksort_sequential (int array[], int p, int r){
    int q;
    if (p < r) {
        q = partition(array, p, r);
        quicksort_sequential(array, p, q - 1);
        quicksort_sequential(array, q + 1, r);
    }
}




void quicksort_paralled (int array[], int p, int r){
    int q;
    q = partition(array, p, r);
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
      
        int ID = omp_get_thread_num();

        if (ID == 0){
        quicksort_sequential(array, p, q);
        }

        if (ID == 1){
        quicksort_sequential(array, q + 1, r);
            
        }
    }    
}




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
       
        fprintf(fp, "The execution time for sorting %d numbers with quicksort method utilizing parallel algorithm is: %Lfs\n", N, time);
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


