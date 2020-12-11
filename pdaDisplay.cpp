#include "pdaHeader.h"
void pdaDisplay(){
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
    return;
}