#include "Engine.h"
#include "Handler.h"
#include <stdlib.h>

Engine* initialEngine(){
    Engine *engine = (Engine*) malloc(sizeof(struct Engine));
    if (engine == NULL){
        printf("Out of memory\n");
        exit(1);
    }
    engine->FEL = create_PRIORITY_QUEUE();
    engine->stationA = create_FIFO();
    engine->stationB = create_FIFO();
    engine->stationC = create_FIFO();
    engine->totaltime = 10000.0;
    engine->systemtime = 0.0;
    return engine;
}

// schedule one new event to the future event list
void schedule(Engine *engine, double timestamp, int event_type){
    insert_event(engine->FEL, timestamp, event_type);
    
}

// run the engine and update the sytstem time
void run(Engine *engine){
    schedule(engine, 0, 0);
    while (engine->FEL->pq_size>0){
        EVENT *event = pop_event(engine->FEL);
        engine->systemtime = event->event_time;
        printf("System time Now is %f and event is %p:\n",engine->systemtime, event);
        if (engine->systemtime>engine->totaltime){
            return;
        }
        process(engine,event);
        free(event);
        
    }
    
    // clear all memory to avoid memory leak
    delete_FIFO(engine->stationA);
    delete_FIFO(engine->stationB);
    delete_FIFO(engine->stationC);
    delete_PRIORITY_QUEUE(engine->FEL);
    
}
