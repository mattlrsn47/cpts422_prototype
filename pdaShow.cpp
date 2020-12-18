#include "pdaHeader.h"

void pdaShow(std::ostream &output){
    if (!pdaObject.open) {
        output << "No PDA is open to show!\n\n";
        return;
    }
    output \
    << "Course:\t\t"<< "Cpts 422" << '\n'\
    << "Semester:\t"<< "Fall" << '\n'\
    << "Year:\t\t"<< "2020" << '\n'\
    << "Instructor:\t"<< "Luis DeLatorre" << '\n'\
    << "Authors:\t"<< "Matt L. Thomas D. Jacob S. Becca H." << '\n'\
    << "Version:\t"<< "Final v1" << '\n';
    output << "(CFG)Transitions Allowed:\t"<< pdaObject.maximumTransitions << '\n';
    output << "(CFG)Maximum Characters:\t"<< pdaObject.maximumCharacters << '\n';
    output << "Pushdown Automaton Name:\t"<< pdaObject.name << '\n';
    output << "Pushdown Automaton Status:\t";
    if (pdaObject.status == NOT_YET_RUN) {
        output << "Has not been run.\n";
    } else if (pdaObject.status == RUNNING) {
        output << "Currently running.\n"\
        << "\tInput string:\t\t" << pdaObject.originalInputString\
        << "\n\tNumber of transitions:\t" << pdaObject.totalTransitions\
        << "\n";
    } else {
        output << "Completed operation.\n"\
        << "\tInput string:\t\t" << pdaObject.originalInputString\
        << "\n\tNumber of transitions:\t" << pdaObject.totalTransitions\
        << "\n\tResult:\t\t\t";
        if (pdaObject.accepted) {
            output << "Accepted\n";
        } else if (pdaObject.rejected) {
            output << "Rejected\n";
        } else {
            output << "Terminated early\n";
        }
    }
    output << "Input Strings Status:\t\t";
    if (pdaObject.stringListChanged) {
        output << "Changes made to list\n";
    } else {
        output << "No changes made\n";
    }
    output << "\n";
}