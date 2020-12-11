#include "pdaHeader.h"

void pdaShow(){
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
    std::cout << "Pushdown Automaton Status:\t"<< pdaObject.status << '\n';
    std::cout << "Input Strings Status:\t\t";
    if (pdaObject.stringListChanged) {
        std::cout << "Changes made to list";
    } else {
        std::cout << "No changes made";
    }
    std::cout << "\n" \
    << "Current/Recent Input String:\t"<< pdaObject.originalInputString << '\n' \
    << "Total Transitions:\t\t"<< pdaObject.totalTransitions << '\n';
}