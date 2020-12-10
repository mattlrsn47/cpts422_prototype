#include "UIHeader.h"

int main(int argc, const char** argv) {
    
    std::string userCommand;
    int commandNumber = 0;    
    while (1){
        printf("Command: ");
        std::cin >> userCommand;
        if ((commandNumber = checkCommand(userCommand)) != 0){
            decipherCommand(commandNumber);
	   
        }else{
            printf("Invalid command, type h/H for help with commands.\n\n");
        }
        
    }

    return 0;
}
