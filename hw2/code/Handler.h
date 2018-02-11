#ifndef Handler_h
#define Handler_h

#include <stdio.h>
#include "Engine.h"
#include "Random.h"

extern double waitingTime;
extern double totalServiceTime;
extern int customer_count;

// determine what process to take according to event type
void process(Engine *engine, EVENT *event);

void arrival(Engine *engine, double current_time);

void ServiceA(Engine *engine, double current_time);

void ServiceB(Engine *engine, double current_time);

void ServiceC(Engine *engine, double current_time);

void departure(Engine *engine, double current_time);



#endif /* Handler_h */
