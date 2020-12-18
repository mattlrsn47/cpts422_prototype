#include "UIHeader.h"

std::istream* input;
std::ostream* output;

void decipherCommand(int cNo){
    input = &std::cin;
    output = &std::cout;
    switch(cNo){
    case CLOSE:
        pdaClose(*output);
        break;
    case DISPLAY:
        pdaDisplay(*output);
        break;
    case EXIT:
        pdaExit(*output);
        break;
    case HELP:
        pdaHelp(*output);
        break;
    case INSERT:
        pdaInsert(*output, *input);
        break;
    case LIST:
        pdaList(*output);
        break;
    case OPEN:
        pdaOpen(*output, *input);
        break;
    case QUIT:
        pdaQuit(*output);
        break;
    case RUN:
        pdaRun(*output, *input);
        break;
    case SET:
        pdaSet(*output, *input);
        break;
    case SHOW:
        pdaShow(*output);
        break;
    case VIEW:
        pdaView(*output);
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
