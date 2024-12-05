/*
This is assignment 5
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include "structs.h"

#ifndef UTILS_H
#define UTILS_H

/*
MY CHANNEL FUNCTIONS
These functions allow me to have a more reliable use of condition varibales
with the mutex and abstract in run functions
*/
void mySignaler(myChannel* channel);

void myReceiver(myChannel* channel);

void myBroadcaster(myChannel* channel);

/*
GET STATUS
Create a string that stores the up to date info about the machine. Stored
via a pointer.
*/
char* status(char* str, Machine* machine);

/*
GET POSITIVE INT
We get the char for the flag, pointer to int where to store and the input
string
*/
void getPosInt(int* num, char flag,char inp[]);
/*
GET OPTIONS
Needed for user input. We get what is given to the main fucntion and store it
in machine struct via pointer.
*/
void getOptions(int argc, char* argv[], Machine* machine);

#endif