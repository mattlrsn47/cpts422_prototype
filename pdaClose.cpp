#include "pdaHeader.h"

void pdaClose(std::ostream &output){
    if (pdaObject.open) {
        output << "Closing PDA....\n\n";
        /* if changes made to input string list, write to file */
        if (pdaObject.stringListChanged) {
            std::ofstream inputStrings(pdaObject.name + ".str");
            int count = 1;
            for (auto s : pdaObject.inputStringList) {
                inputStrings << s;
                count++;
                if (count <= pdaObject.inputStringList.size()) {
                    inputStrings << std::endl;
                }
            }
            inputStrings.close();
            if (inputStrings.bad()) {
                output << "Failed to write input strings to " << pdaObject.name << ".str\n";
            }
            output << "Successfully wrote input strings to " << pdaObject.name << ".str\n\n";
        }
        pdaObject = PdaObject(); // reset pda object
    } else {
        output << "No PDA was open!\n\n";
    }
    return;
}