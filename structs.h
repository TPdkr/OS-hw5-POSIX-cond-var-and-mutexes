/*
This is assignment 5
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <pthread.h>

#ifndef STRUCTS_H
#define STRUCTS_H

/*
MYCHANNEL
This struct is used for communication between threads.
*/
typedef struct {
    int received;//was the message reveived?
    pthread_mutex_t signalMt;
    pthread_cond_t signal;
} myChannel;

/*
MACHINE
This stores the machine information and needed structs like mutex and channels
*/
typedef struct {
    int coins;//how many coins in machine?
    int inserted;//how many coins did the user insert?
    int drinksLeft;//how many drinks left?
    int capacity;//the max drinks number
    int students;//number of student to be served
    int price;//the drink price
    int isFirst;//because the first doesn't peint that they waited

    myChannel* toStudent;//channel for communication with student
    myChannel* toSupplier;//same but for supplier
    pthread_mutex_t StMutex;//student mutex so they dont overlap
    pthread_mutex_t machineState;//machine state mutex
} Machine;

/*
STUDENT
This struct stores the student information(num) and machine pointer
*/
typedef struct {
    int num;
    Machine* machine; 
} Student;

/*
INIT - these functions initate the structs
*/
void machineInit(Machine* machine, myChannel* toStudent, myChannel* toSupplier);

void myChannelInit(myChannel* channel);

/*
DESTROY/KILL - these function destroy the structs after they are no longer needed
*/
void myChannelDestroy(myChannel* channel);

void machineKill(Machine* machine);

#endif