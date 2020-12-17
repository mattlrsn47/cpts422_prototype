#include "UIHeader.h"

void decipherCommand(int cNo){
    switch(cNo){
    case CLOSE:
        pdaClose();
        break;
    case DISPLAY:
        pdaDisplay();
        break;
    case EXIT:
        pdaExit(std::cout);
        break;
    case HELP:
        pdaHelp();
        break;
    case INSERT:
        pdaInsert();
        break;
    case LIST:
        pdaList();
        break;
    case OPEN:
        pdaOpen();
        break;
    case QUIT:
        pdaQuit();
        break;
    case RUN:
        pdaRun();
        break;
    case SET:
        pdaSet();
        break;
    case SHOW:
        pdaShow();
        break;
    case VIEW:
        pdaView();
        break;
    default:
        break;
    }
}
int checkCommand(std::string commandString){
    int strLength = commandString.length();
    if (strLength != 1){
       return 0;
    }
    char currentChar = commandString[0];
    if (currentChar == 'c' || currentChar == 'C'){
        return CLOSE;
    }else if(currentChar == 'p' || currentChar == 'P') {
        return DISPLAY;
    }else if(currentChar == 'x' || currentChar == 'X') {
        return EXIT;
    }else if(currentChar == 'h' || currentChar == 'H'){
        return HELP;
    }else if(currentChar == 'i' || currentChar == 'I'){
        return INSERT;
    }else if(currentChar == 'l' || currentChar == 'L'){
        return LIST;
    }else if(currentChar == 'o' || currentChar == 'O'){
        return OPEN;
    }else if(currentChar == 'q' || currentChar == 'Q'){
        return QUIT;
    }
    else if (currentChar == 'r' || currentChar == 'R'){
        return RUN;
    }else if(currentChar == 'e' || currentChar == 'E'){
        return SET;
    }
    else if (currentChar == 'w' || currentChar == 'W'){
        return SHOW;
    }else if (currentChar == 'v' || currentChar == 'V'){
        return VIEW;
    }else{
        return 0;
    }
}
