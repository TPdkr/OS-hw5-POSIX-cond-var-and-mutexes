/*
This is assignment 5
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "machine.h"
#include "utils.h"

//START DAY====================================================================
void startDay(int argc, char* argv[]){
    //we create the structs
    myChannel toStudent[5], toSupplier[2];
    Machine machine;
    //Machine is initated
    machineInit(&machine, toStudent, toSupplier);
    //input is processed
    getOptions(argc,argv,&machine);
    Student students[machine.students];

    //we create machine and supplier
    pthread_t tids[machine.students+2];
    (void) pthread_create(&tids[0], NULL, runMachine, &machine);
    (void) pthread_create(&tids[1], NULL, runSupplier, &machine);
    
    //we create students
    for(int i=0;i<machine.students;i++){
        students[i].num = i;
        students[i].machine = &machine;
        (void) pthread_create(&tids[i+2], NULL, runStudent, &students[i]);
    }
    //we wait for them to finish
    for(int i=0;i<machine.students;i++){
        (void) pthread_join(tids[i+2], NULL);
    }
    (void) pthread_join(tids[1], NULL);
    (void) pthread_join(tids[0], NULL);
    //machine is killed
    machineKill(&machine);
}

//RUN MACHINE==================================================================
void* runMachine(void* inp){
    //we get the input variables
    char str[100];
    Machine* machine = (Machine*) inp;
    myChannel* channels = machine->toStudent;
    myChannel* techSupport = machine->toSupplier;

    printf("energy: %s machine booting up\n", status(str,machine));
    //no drinks at the start, need to signal to supplier
    if(machine->drinksLeft<=0){
            mySignaler(&techSupport[0]);
            myReceiver(&techSupport[1]);
    }

    for(int i=0;i<machine->students;i++){
        //no drinks, need to signal to supplier
        if(machine->drinksLeft<=0){
            mySignaler(&techSupport[0]);
            myReceiver(&techSupport[1]);
        }
        //did the student arrive?
        myReceiver(&channels[0]);
        printf("energy: %s machine waiting for more coins\n", status(str,machine));
        mySignaler(&channels[1]);
        //we are starting to process a stident
        myReceiver(&channels[2]);//did the student pay?

        //dispensing a drink, we are editing machine state
        (void) pthread_mutex_lock(&machine->machineState); 
        machine->drinksLeft--;
        machine->coins+=machine->price;
        machine->inserted=0;
        printf("energy: %s machine dispensing a drink\n", status(str,machine));
        (void) pthread_mutex_unlock(&machine->machineState);

        //we say that drink was dispensed
        printf("energy: %s machine waiting for pickup of drink\n", status(str,machine));
        mySignaler(&channels[3]);//we say that we dispensed a drink
        myReceiver(&channels[4]);//we wait for user to pick up the drink
    }
    printf("energy: %s machine waiting for more coins\n", status(str,machine));
    return NULL;

}

//RUN STUDENT==================================================================
void* runStudent(void* inp){
    //we get the input variables
    char str[100];
    Student* student = (Student*) inp;
    Machine* machine = student->machine;
    myChannel* channels = machine->toStudent;
    myChannel* techSupport = machine->toSupplier;
    printf("energy: %s student %d established\n", status(str,machine), student->num);
    printf("energy: %s student %d requires an energy drink\n", status(str,machine), student->num);
    //we see if machine needs to be refilled when we arrive
    if(machine->drinksLeft<=0){
        printf("energy: %s student %d waiting for machine to be refilled\n", status(str,machine), student->num);
        while(machine->drinksLeft<=0){
            myReceiver(&techSupport[1]);
        }
    }
    //only 1 student can edit
    (void) pthread_mutex_lock(&machine->StMutex); 
    //we wait for machine to be refilled when it is our turn
    if(machine->drinksLeft<=0){
        printf("energy: %s student %d waiting for machine to be refilled\n", status(str,machine), student->num);
        while(machine->drinksLeft<=0){
            myReceiver(&techSupport[1]);
        }
    }
    //we need to print if we waited
    if(machine->isFirst){
        (void) pthread_mutex_lock(&machine->machineState); 
        machine->isFirst=0;//we change machine state
        (void) pthread_mutex_unlock(&machine->machineState);
    } else {
        printf("energy: %s student %d waiting for the machine\n",status(str,machine), student->num);
    }

    mySignaler(&channels[0]);//we are here. we signal the machine
    myReceiver(&channels[1]);//waiting for it to signal back
    printf("energy: %s student %d is next to be served\n",status(str,machine), student->num);

    //we edit the state of the machine by inserting coins
    (void) pthread_mutex_lock(&machine->machineState); 
    for(int i=0;i<machine->price;i++){
        machine->inserted++;
        printf("energy: %s student %d inserted another coin\n",status(str,machine), student->num);
        
    }
    (void) pthread_mutex_unlock(&machine->machineState);

    //we signal that we payed
    printf("energy: %s student %d waiting for drink to arrive\n", status(str,machine), student->num);
    mySignaler(&channels[2]);
    //we wait for the drink to be dispensed
    myReceiver(&channels[3]);
    //we tell the machine that we picked up a drink
    printf("energy: %s student %d picked up a drink\n",status(str,machine), student->num);
    printf("energy: %s student %d enjoying an energy drink\n",status(str,machine), student->num);
    mySignaler(&channels[4]);
    //we can let other student a go
    (void) pthread_mutex_unlock(&machine->StMutex);
    return NULL;
}

//RUN SUPPLIER=================================================================
void* runSupplier(void* inp){
    //local variables
    char str[100];
    int rounds;
    //we get the input
    Machine* machine = (Machine*) inp;
    myChannel* channels = machine->toSupplier;
    rounds = (machine->students+machine->capacity-1)/machine->capacity;
    printf("energy: %s supplier established\n",status(str,machine));
    //we wait for someone to tell us that we need to refill
    for(int i=0;i<rounds;i++){
        myReceiver(&channels[0]);
        //we cant have anyone else changing machine state
        (void) pthread_mutex_lock(&machine->machineState);
        printf("energy: %s supplier arriving\n",status(str,machine));
        printf("energy: %s supplier loading %d drinks\n",status(str,machine), machine->capacity);
        machine->drinksLeft=machine->capacity;
        
        int gathered = machine->coins;
        machine->coins=0;
        printf("energy: %s supplier collected %d coins\n",status(str,machine), gathered);
        printf("energy: %s supplier leaving\n",status(str,machine));

        //we are leaving and can let others change the machine state
        (void) pthread_mutex_unlock(&machine->machineState); 
        //mySignaler(&channels[1]);
        myBroadcaster(&channels[1]);
    }    
    return NULL;
}