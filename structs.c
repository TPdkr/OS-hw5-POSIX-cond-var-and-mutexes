/*
This is assignment 5
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "structs.h"

//MACHINE INIT
void machineInit(Machine* machine, myChannel* toStudent, myChannel* toSupplier){
    //we set the default values
    machine->toStudent=toStudent;
    machine->toSupplier=toSupplier;
    machine->students=2;
    machine->capacity=4;
    machine->drinksLeft=0;
    machine->inserted=0;
    machine->coins=0;
    machine->price=5;
    machine->isFirst=1;
    //all the channels need to be initalized
    for(int i=0;i<5;i++){
        myChannelInit(&machine->toStudent[i]);
    }
    for(int i=0;i<2;i++){
        myChannelInit(&machine->toSupplier[i]);
    }
    //we need to init the mutexess
    pthread_mutex_init(&machine->StMutex, NULL);
    pthread_mutex_init(&machine->machineState, NULL);
}
//MY CHANNEL INIT
void myChannelInit(myChannel* channel){
    //we set the starting value and initiate the mutex and condition variable
    channel->received = 0;
    pthread_mutex_init(&channel->signalMt, NULL);
    pthread_cond_init(&channel->signal, NULL);
}
//MACHINE KILL
void machineKill(Machine* machine){
    //we destiry the mutexes
    pthread_mutex_destroy(&machine->StMutex);
    pthread_mutex_destroy(&machine->machineState);
    //channels are destroyed
    for(int i=0;i<5;i++){
        myChannelDestroy(&machine->toStudent[i]);
    }
    for(int i=0;i<2;i++){
        myChannelDestroy(&machine->toSupplier[i]);
    }
}
//MY CHANNEL DESTORY
void myChannelDestroy(myChannel* channel){
    //we destroy the mutex and condition variable
    pthread_mutex_destroy(&channel->signalMt);
    pthread_cond_destroy(&channel->signal);
}