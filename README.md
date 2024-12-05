# Assignment 5
## Submitted by Timofei Podkorytov
for operating systems course in fall 2024

## Compiling: Makefile
The following make commands are available:
```
$ make energy
```
This compiles all files into machine executable that accepts user input. It can get 'n' and 'c' options followed by a positive integer.
## Running:
Runs the main function and produces the avergae times for all scenarious:

```./energy``` - the only input we can give is the option listed above

## Files:
- Makefile
- README.md
- A51.md
- emergy.c
- utils.h
- utils.c
- machine.h
- machine.c
- structs.h
- structs.c

Makefile provides make commands. README gives the description of the overall
homework submission.

Energy file has the main function that calls evrything else. 

Utils has functions that are needed for input and other things to make the code functional.

Machine has the run functions for each subject: machine, student, supplier.

Structs has all the structs and functions needed for their initalization as well as destruction.

A51.md has the soultion of the first problem.
## Output
For input ```./energy``` something similar to the following output is likely to be produced. I want to note that certain parts like order of establihment of student may very depending on your system and chance. 

```
energy: [0/4 drinks, 0 coins, 0 inserted] machine booting up
energy: [0/4 drinks, 0 coins, 0 inserted] student 0 established
energy: [0/4 drinks, 0 coins, 0 inserted] student 0 requires an energy drink
energy: [0/4 drinks, 0 coins, 0 inserted] student 0 waiting for machine to be refilled
energy: [0/4 drinks, 0 coins, 0 inserted] supplier established
energy: [0/4 drinks, 0 coins, 0 inserted] supplier arriving
energy: [0/4 drinks, 0 coins, 0 inserted] supplier loading 4 drinks
energy: [4/4 drinks, 0 coins, 0 inserted] supplier collected 0 coins
energy: [4/4 drinks, 0 coins, 0 inserted] supplier leaving
energy: [4/4 drinks, 0 coins, 0 inserted] machine waiting for more coins
energy: [4/4 drinks, 0 coins, 0 inserted] student 1 established
energy: [4/4 drinks, 0 coins, 0 inserted] student 1 requires an energy drink
energy: [4/4 drinks, 0 coins, 0 inserted] student 0 is next to be served
energy: [4/4 drinks, 0 coins, 1 inserted] student 0 inserted another coin
energy: [4/4 drinks, 0 coins, 2 inserted] student 0 inserted another coin
energy: [4/4 drinks, 0 coins, 3 inserted] student 0 inserted another coin
energy: [4/4 drinks, 0 coins, 4 inserted] student 0 inserted another coin
energy: [4/4 drinks, 0 coins, 5 inserted] student 0 inserted another coin
energy: [4/4 drinks, 0 coins, 5 inserted] student 0 waiting for drink to arrive
energy: [3/4 drinks, 5 coins, 0 inserted] machine dispensing a drink
energy: [3/4 drinks, 5 coins, 0 inserted] machine waiting for pickup of drink
energy: [3/4 drinks, 5 coins, 0 inserted] student 0 picked up a drink
energy: [3/4 drinks, 5 coins, 0 inserted] student 0 enjoying an energy drink
energy: [3/4 drinks, 5 coins, 0 inserted] student 1 waiting for the machine
energy: [3/4 drinks, 5 coins, 0 inserted] machine waiting for more coins
energy: [3/4 drinks, 5 coins, 0 inserted] student 1 is next to be served
energy: [3/4 drinks, 5 coins, 1 inserted] student 1 inserted another coin
energy: [3/4 drinks, 5 coins, 2 inserted] student 1 inserted another coin
energy: [3/4 drinks, 5 coins, 3 inserted] student 1 inserted another coin
energy: [3/4 drinks, 5 coins, 4 inserted] student 1 inserted another coin
energy: [3/4 drinks, 5 coins, 5 inserted] student 1 inserted another coin
energy: [3/4 drinks, 5 coins, 5 inserted] student 1 waiting for drink to arrive
energy: [2/4 drinks, 10 coins, 0 inserted] machine dispensing a drink
energy: [2/4 drinks, 10 coins, 0 inserted] machine waiting for pickup of drink
energy: [2/4 drinks, 10 coins, 0 inserted] student 1 picked up a drink
energy: [2/4 drinks, 10 coins, 0 inserted] student 1 enjoying an energy drink
energy: [2/4 drinks, 10 coins, 0 inserted] machine waiting for more coins
```