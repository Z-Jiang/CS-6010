#ifndef Engine_h
#define Engine_h

#include <stdio.h>
#include "PRIORITY.h"
#include "FIFO.h"


typedef struct Engine{
    PRIORITY *FEL;
    FIFO *stationA;
    FIFO *stationB;
    FIFO *stationC;
    double totaltime;
    double systemtime;
} Engine;

Engine* initialEngine();

void schedule(Engine *engine, double timestamp, int event_type);

void run(Engine *engine);

#endif /* DiscreteEventSimulation_h */
