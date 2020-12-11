#include "pdaHeader.h"

void pdaClose(){
    std::cout << "WORK IN PROGRESS.....\n";
    if (pdaObject.open) {
        std::cout << "Closing PDA....\n\n";
        /* IF CHANGES MADE TO INPUT STRING LIST, WRITE TO FILE */
        if (pdaObject.stringListChanged) {
            // write to file
        }
        pdaObject = PdaObject(); // reset pda object
    } else {
        std::cout << "No PDA was open!\n\n";
    }
    return;
}