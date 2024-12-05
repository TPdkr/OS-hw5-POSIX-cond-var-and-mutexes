/*
This is assignment 5
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include "utils.h"

#ifndef MACHINE_H
#define MACHINE_H

/*
START DAY
This function starts a day in the context of the problem
*/
void startDay(int argc, char* argv[]);

/*
RUN MACHINE
This function reveivers a void pointer to machine struct and runs
the machine.
*/
void* runMachine(void * inp);
/*
RUN STUDENT
This function reveivers a void pointer to Student struct and runs
the student.
*/
void* runStudent(void * inp);
/*
RUN SUPPLIER
This function reveivers a void pointer to machine struct and runs
the supplier.
*/
void* runSupplier(void* inp);

#endif