#include "Random.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>


// to genereate a random ""double" number uniformly distributed over the interval [0,1).
double urand (){
    double rand_num;

    rand_num = (double)rand() /RAND_MAX;
    
    return rand_num;
}

//to generate a random number from an exponential distribution with mean U.
double randexp(double U){
    double random_exp;
    random_exp = - (U * log(1.0 - urand()));
    
    return random_exp;
}
