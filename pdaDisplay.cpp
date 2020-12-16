#include "pdaHeader.h"
void pdaDisplay(){
    if (pdaObject.open) {
        /* loop over branch list and output their paths */          
        if (pdaObject.status == NOT_YET_RUN) {
            std::cout << "No paths yet traversed\n\n";
            return;
        }
        for (auto b : pdaObject.branchList) {
            std::cout << "Path " << b.id << ". ";
            std::cout << b.path << "\n";
        }
        std::cout << "\n";
    } else {
        std::cout << "No PDA is open to display!\n\n";
    }
    return;
}