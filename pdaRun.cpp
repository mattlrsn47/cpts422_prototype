#include "pdaHeader.h"

void pdaRun(){
    if (!pdaObject.open) {
        std::cout << "No PDA is open to run!\n\n";
        return;
    }
    if (pdaObject.status != RUNNING) {
        // not already running, so initialize
        // get input string number
        int userInputStringNumber;
        std::string line;
        std::cout << "Input string number in list: ";
        std::cin >> userInputStringNumber;
        // if number > number of strings in list or < 1, invalid
        if (userInputStringNumber > pdaObject.inputStringList.size() || userInputStringNumber < 1) {
            std::cout << "Invalid input string number!\n\n";
            return;
        }
        
        std::cout << "Initializing...\n";
        pdaObject.accepted = false;
        pdaObject.rejected = false;
        pdaObject.status = RUNNING;
        pdaObject.totalTransitions = 0;
        // grab string from list by its index using an iterator
        std::list<std::string>::iterator stringItr = pdaObject.inputStringList.begin();
        std::advance(stringItr, userInputStringNumber-1);
        pdaObject.originalInputString = (*stringItr);
        // create starting stack
        std::stack<char> initialStack;
        initialStack.push(pdaObject.startCharacter);
        // create the "root" branch/path
        pdaObject.branchList = {Branch(1, pdaObject.initialState, pdaObject.originalInputString, initialStack, 0, pdaObject.initialState)};

        // show instantaneous description before first transition
        std::list<Branch>::iterator branchItr = pdaObject.branchList.begin();
        std::cout << "PATH " << (*branchItr).id << std::endl;
        std::cout << (*branchItr).numTransitions << ". (";
        std::cout << (*branchItr).currentState << ", ";
        std::cout << (*branchItr).truncateInputString(pdaObject.maximumCharacters) << ", ";
        std::cout << (*branchItr).stackToString(pdaObject.maximumCharacters) << ")\n\n";
    }
    // do number of transtitions indicated by maximumTransitions on each branch
    //int ifThisIsStillZeroAllRejected = 0;
    int checkIfNoTransitions = pdaObject.totalTransitions;
    std::list<Branch>::iterator b;

    for (b = pdaObject.branchList.begin(); b != pdaObject.branchList.end(); b++) {
        int i = pdaObject.maximumTransitions + 1;
        //std::cout << "exploring b" << (*b).id << "\n"; // for testing
        while (i > 0) {
            // check if current state is final state
            for (auto s : pdaObject.finalStateList) {
                if (s == (*b).currentState) {
                    (*b).accepted = true;
                    pdaObject.accepted = true;
                    pdaObject.status = NOT_RUNNING;
                    // YAY ACCEPTED print last instantaneous desc.
                    std::cout << "PATH " << (*b).id << std::endl;
                    std::cout << (*b).numTransitions << ". (";
                    std::cout << (*b).currentState << ", ";
                    std::cout << (*b).truncateInputString(pdaObject.maximumCharacters) << ", ";
                    std::cout << (*b).stackToString(pdaObject.maximumCharacters) << ")\n";
                    // print accepted message and return to stop running
                    std::cout << "Input string " << pdaObject.originalInputString;
                    std::cout << " accepted in " << (*b).numTransitions;
                    std::cout << " transitions!\n\n";
                    pdaObject.totalTransitions = (*b).numTransitions;
                    return;
                }
            }
            if (i > 1 && (*b).rejected == false) {
                // find applicable transitions
                //std::cout << "searching transitions for b" << (*b).id << "...\n"; // for testing
                std::list<Transition> possibleTransitions;
                for (auto t : pdaObject.transitionList) {
                    if (t.startState == (*b).currentState &&
                        t.startInput == (*b).remainingInputString.at(0) &&
                        t.startChar == (*b).currentStack.top()) {
                        //std::cout << "found one t\n"; // for testing
                        possibleTransitions.push_back(t);
                    }
                }
                // if found, update
                if (!possibleTransitions.empty()) {
                    //ifThisIsStillZeroAllRejected++;
                    pdaObject.totalTransitions++;
                    // some updates and copies in case of branching:
                    // update remaining string in a temp value
                    std::string tempStr = (*b).remainingInputString;
                    tempStr.erase(tempStr.begin());
                    if (tempStr == "") {
                        tempStr = "\\"; // char the represents empty string
                    }
                    // edit numTransitions in temp
                    int tempNum = (*b).numTransitions + 1;
                    // make copy of stack
                    std::stack<char> tempStk = (*b).currentStack;
                    // make copy of path
                    std::string tempPath = (*b).path;

                    std::list<Transition>::iterator tItr;

                    int counter = 0;
                    for (tItr = possibleTransitions.begin(); tItr != possibleTransitions.end(); tItr++) {
                        
                        std::stack<char> thisStack = tempStk;
                        if ((*tItr).endChar == "\\") {
                            thisStack.pop();
                            if (thisStack.empty()){
                                thisStack.push('\\'); // empty stack symbol
                            }
                        } else if ((*tItr).endChar != (std::string(1,(*tItr).startChar))) {
                            thisStack.push((*tItr).endChar.at(0));
                        }
                        std::string thisPath = tempPath + "->" + (*tItr).endState;

                        if (counter == 0) {
                            // update current branch
                            (*b).currentState = (*tItr).endState;
                            (*b).currentStack = thisStack;
                            (*b).remainingInputString = tempStr;
                            (*b).numTransitions = tempNum;
                            (*b).path = thisPath;
                            //std::cout << "b" << (*b).id << " updated\n"; // for testing
                        } else {
                            // create new branch to match transition
                            Branch newBranch = Branch(pdaObject.branchList.size()+1, (*tItr).endState, tempStr, thisStack, tempNum, thisPath);
                            pdaObject.branchList.push_back(newBranch);
                        }
                        counter++;
                    }
                } else {
                    (*b).rejected = true;
                    // if ((*b).rejected) {
                    //     std::cout << "b" << (*b).id << " rejected\n"; // for testing
                    // }
                }

                // check if already at rejection point
                possibleTransitions.clear();
                for (auto t : pdaObject.transitionList) {
                    if (t.startState == (*b).currentState &&
                        t.startInput == (*b).remainingInputString.at(0) &&
                        t.startChar == (*b).currentStack.top()) {
                        possibleTransitions.push_back(t);
                    }
                }
                bool finalState = false;
                for (auto s : pdaObject.finalStateList) {
                    if (s == (*b).currentState) {
                        finalState = true;
                    }
                }
                if (possibleTransitions.empty() && !finalState) {
                    (*b).rejected = true;
                    // if ((*b).rejected) {
                    //     std::cout << "b" << (*b).id << " rejected\n"; // for testing
                    // }
                }
            }
            i--;
        }
        // print most recent instantaneous description
        if ((*b).numTransitions != 0 && (*b).rejected == false) {
            std::cout << "PATH " << (*b).id << std::endl;
            std::cout << (*b).numTransitions << ". (";
            std::cout << (*b).currentState << ", ";
            std::cout << (*b).truncateInputString(pdaObject.maximumCharacters) << ", ";
            std::cout << (*b).stackToString(pdaObject.maximumCharacters) << ")\n\n";
        }
    }
    if (checkIfNoTransitions == pdaObject.totalTransitions) {
        // num of transitions did not change, so all branches rejected
        pdaObject.rejected = true;
        pdaObject.status = NOT_RUNNING;
        std::cout << "Input string " << pdaObject.originalInputString;
        std::cout << " rejected in " << pdaObject.totalTransitions;
        std::cout << " transitions!\n\n";
    }
    return;
}