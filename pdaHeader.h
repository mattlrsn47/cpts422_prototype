#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#define DELETE

#define CLOSE 1
#define DISPLAY 2
#define EXIT 3
#define HELP 4
#define INSERT 5
#define LIST 6
#define OPEN 7
#define QUIT 8
#define RUN 9 
#define SET 10
#define SHOW 11
#define VIEW 12

// pda functions
void pdaClose();
void pdaDisplay();
void pdaExit();
void pdaHelp();
void pdaInsert();
void pdaList();
void pdaOpen();
void pdaQuit();
void pdaRun();
void pdaSet();
void pdaShow();
void pdaView();


void decipherCommand(int cNo);
int checkCommand(std::string commandString);


//  prototype.cpp
