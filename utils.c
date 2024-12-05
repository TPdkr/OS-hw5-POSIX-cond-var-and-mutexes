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

#include "utils.h"
#include "machine.h"
#include "structs.h"

//MY SIGNALER------------------------------------------------------------------
void mySignaler(myChannel* channel){
    int init=channel->received;//initial value
    while(channel->received==init){
        //we signal until the confirmation that a signal was delivered
        (void) pthread_mutex_lock(&channel->signalMt); 
        pthread_cond_signal(&channel->signal);
        (void) pthread_mutex_unlock(&channel->signalMt); 
    }
}

//MY RECEIVER------------------------------------------------------------------
void myReceiver(myChannel* channel){
    //we lock and wait
    (void) pthread_mutex_lock(&channel->signalMt); 
    pthread_cond_wait(&channel->signal, &channel->signalMt);
    channel->received+=1;//we tell that a message was received
    (void) pthread_mutex_unlock(&channel->signalMt);
}

void myBroadcaster(myChannel* channel){
    //we broadcast
    (void) pthread_mutex_lock(&channel->signalMt); 
    pthread_cond_broadcast(&channel->signal);
    (void) pthread_mutex_unlock(&channel->signalMt); 
}

//GET POSITIVE INT-------------------------------------------------------------
void getPosInt(int* num, char flag,char inp[]){
    int suc=sscanf(inp, "%d", num);
    //is the arguemnt int check
    if (suc!=1){
        fprintf(stderr, "energy: invalid number %s for -%c option\n", inp,flag);
        exit(1);
    }
    //invalid int check
    if(*num<=0){
        fprintf(stderr,"energy: value %d for -%c option should be >= 1\n", *num,flag);
        exit(1);
    }
}
//GET OPTIONS------------------------------------------------------------------
void getOptions( int argc, char* argv[], Machine* machine){
    //the argument position
    int argPos=1;
    //we set default values
    //machineInit(machine, toStudent, toSuppliers);
    int opt;
    //we use getopt for options
    while((opt = getopt(argc, argv, ":n:c:"))!=-1){
        switch(opt){
            case 'n':
                getPosInt(&machine->students,'n',optarg);
                argPos+=2;
                break;
            case 'c':
                getPosInt(&machine->capacity,'c',optarg);
                argPos+=2;
                break;
            case ':'://nothing to be done but call an error
            case '?'://unknown flag meaning invalid input
                fprintf(stderr,"energy: invalid option '%c'\n", opt);
                exit(1);
                break;
        }
    }
    //is there still something left? ERROR in input
    if(argv[argPos]!=NULL){
        fprintf(stderr,"energy: too many arguments supplied\n");
        exit(EXIT_FAILURE);
    }
}

//GET STATUS-------------------------------------------------------------------
char* status(char* str, Machine* machine){
    sprintf(str,"[%d/%d drinks, %d coins, %d inserted]", machine->drinksLeft, \
    machine->capacity, machine->coins, machine->inserted);
    return str;
}

