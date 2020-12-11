#include "pdaHeader.h"

void pdaShow(){
    if (!pdaObject.open) {
        std::cout << "No PDA is open to show!\n\n";
        return;
    }
    std::cout \
    << "Course:\t\t"<< "Cpts 422" << '\n'\
    << "Semester:\t"<< "Fall" << '\n'\
    << "Year:\t\t"<< "2020" << '\n'\
    << "Instructor:\t"<< "Luis DeLatorre" << '\n'\
    << "Authors:\t"<< "Matt L. Thomas D. Jacob S. Becca H." << '\n'\
    << "Version:\t"<< "Final v1" << '\n';
    std::cout << "(CFG)Transitions Allowed:\t"<< pdaObject.maximumTransitions << '\n';
    std::cout << "(CFG)Maximum Characters:\t"<< pdaObject.maximumCharacters << '\n';
    std::cout << "Pushdown Automaton Name:\t"<< pdaObject.name << '\n';
    std::cout << "Pushdown Automaton Status:\t";
    if (pdaObject.status == NOT_YET_RUN) {
        std::cout << "Has not been run.\n";
    } else if (pdaObject.status == RUNNING) {
        std::cout << "Currently running.\n"\
        << "\tInput string:\t\t" << pdaObject.originalInputString\
        << "\n\tNumber of transitions:\t" << pdaObject.totalTransitions\
        << "\n";
    } else {
        std::cout << "Completed operation.\n"\
        << "\tInput string:\t\t" << pdaObject.originalInputString\
        << "\n\tNumber of transitions:\t" << pdaObject.totalTransitions\
        << "\n\tResult:\t\t\t";
        if (pdaObject.accepted) {
            std::cout << "Accepted\n";
        } else if (pdaObject.rejected) {
            std::cout << "Rejected\n";
        } else {
            std::cout << "Terminated early\n";
        }
    }
    std::cout << "Input Strings Status:\t\t";
    if (pdaObject.stringListChanged) {
        std::cout << "Changes made to list\n";
    } else {
        std::cout << "No changes made\n";
    }
    std::cout << "\n";
}