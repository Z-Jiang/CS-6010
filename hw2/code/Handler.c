#include "Handler.h"
#include <stdlib.h>


// take different action according to event type
void process(Engine *engine, EVENT *event){
    if (event->event_type == 0){
        arrival(engine, event->event_time);
    }
    else if (event->event_type==1){
        ServiceA(engine, event->event_time);
    }
    else if (event->event_type==2){
        ServiceB(engine, event->event_time);
    }
    else if (event->event_type==3){
        ServiceC(engine, event->event_time);
    }
    else {
        departure(engine, event->event_time);
    }
}

// customers arriving at source
void arrival(Engine *engine, double current_time){
    double service_time = randexp(10);
    double interarrival = randexp(10);
    add_part(service_time, current_time, engine->stationA);
    schedule(engine,current_time + interarrival,0);
    totalServiceTime = totalServiceTime + service_time;
    schedule(engine, current_time, 1);            //?????????????????????????????
    
    printf("The customer arrived.\n");
}

// customers served in A
void ServiceA(Engine *engine, double current_time){
    PART *part = pop_part(engine->stationA);
    waitingTime = waitingTime + current_time - part->enter_time;
    totalServiceTime = totalServiceTime + part->service_time;
    add_part(part->service_time, current_time, engine->stationB);
    if (engine->stationB->counter==1){
        schedule(engine, current_time + part->service_time, 2);
    }
    if (engine->stationA->counter > 0){
        schedule(engine, current_time+part->service_time, 1);
    }
    
    printf("The customer in station A is being served.\n");
    free(part);
    
}

// customers served in B
void ServiceB(Engine *engine, double current_time){
    PART *part = pop_part(engine->stationB);
    waitingTime = waitingTime+current_time-part->enter_time;
    totalServiceTime = totalServiceTime + part->service_time;
    add_part(part->service_time, current_time, engine->stationC);
    if (engine->stationC->counter==1){
        schedule(engine, current_time + part->service_time, 3);
    }
    if (engine->stationB->counter >0){
        schedule(engine, current_time+part->service_time, 2);
    }
    
    printf("The customer in station B is being served.\n");
    free(part);
    
}

// customers served in C
void ServiceC(Engine *engine, double current_time){
    PART *part = pop_part(engine->stationC);
    waitingTime = waitingTime+current_time-part->enter_time;
    schedule(engine, current_time + part->service_time, 4);
    if (engine->stationC->counter >0){
        schedule(engine, current_time+part->service_time, 3);
    }
    
    printf("The customer in station C is being served.\n");
    free(part);
    
}

// customers reach sink and leave the simulation
void departure(Engine *engine, double current_time){
    customer_count++;
    printf("Customer left the simulation process.\n");
    
}
