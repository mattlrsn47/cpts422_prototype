#include "pdaHeader.h"
void pdaDisplay(std::ostream &output){
    if (pdaObject.open) {
        /* loop over branch list and output their paths */          
        if (pdaObject.status == NOT_YET_RUN) {
            output << "No paths yet traversed\n\n";
            return;
        }
        for (auto b : pdaObject.branchList) {
            output << "Path " << b.id << ". ";
            output << b.path << "\n";
        }
        output << "\n";
    } else {
        output << "No PDA is open to display!\n\n";
    }
    return;
}