#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
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

void pdaClose(std::ostream &output);
void pdaDisplay(std::ostream &output);
void pdaExit(std::ostream &output);
void pdaHelp(std::ostream &output);
void pdaInsert(std::ostream &output, std::istream &input);
void pdaList(std::ostream &output);
void pdaOpen(std::ostream &output, std::istream &input);
void pdaQuit(std::ostream &output);
void pdaRun(std::ostream &output, std::istream &input);
void pdaSet(std::ostream &output, std::istream &input);
void pdaShow(std::ostream &output);
void pdaView(std::ostream &output);


void decipherCommand(int cNo);
int checkCommand(std::string commandString);