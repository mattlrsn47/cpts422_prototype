#include "pdaHeader.h"
#include "UIHeader.h"
#include <limits>  

/******* Class functions ******/

//          PDAOBJECT
PdaObject::PdaObject(/* args */){
}

PdaObject::~PdaObject(){
}

//          BRANCH
Branch::Branch(int branchID, std::string cstate, std::string ris, std::stack<char> cstack, int nt, std::string p) {
    id = branchID;
    currentState = cstate;
    remainingInputString = ris;
    currentStack = cstack;
    accepted = false;
    rejected = false;
    numTransitions = nt;
    path = p;
    // some data is cloned from branching point, so be sure to create a branch THEN run the appropriate transition on it
}

Branch::~Branch(){

}

std::string Branch::stackToString(){
    std::stack<char> temp = currentStack;
    std::string stringStack;
    while (!temp.empty()) {
        stringStack.push_back(temp.top());
        temp.pop();
    }
    return stringStack;
}

//          TRANSITION
Transition::Transition(std::string ss, char si, char sc, std::string es, std::string ec){
    startState=ss;
    startInput=si;
    startChar=sc;

    endState=es;
    endChar=ec;
}

Transition::~Transition(){
}
/*****************************/
void pdaClose(){
    std::cout << "Closing PDA....\n";
    pdaObject = PdaObject(); // reset pda object
}

void pdaDisplay(){
    /* LOOP OVER BRANCHLIST AND OUTPUT BRANCH.PATH */          
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

void pdaExit(){
    /* SAVE INPUT STRING LIST TO STRING FILE */
    printf("Successfully exited application\n\n");
    exit(0);
    return;
}
void pdaHelp(){
    std::cout \
    << "|C|lose             Close pushdown automaton\n" \
    << "Dis|p|lay           Display complete paths through pushdown automaton\n" \
    << "E|x|it              Exit application\n" \
    << "|H|elp              Help user\n" \
    << "|I|nsert            Insert input string into list\n" \
    << "|L|ist              List input strings\n" \
    << "|O|pen              Open pushdown automaton\n" \
    << "|Q|uit              Quit operation of pushdown automation on input string\n" \
    << "|R|un               Run pushdown automaton on input string\n" \
    << "S|e|t               Set maximum number of transitions to perform\n"  \
    << "Sho|w|              Show status of application\n"  \
    << "|V|iew              View pushdown automaton\n\n";

    return;
}
void pdaInsert(){
    std::string userInputString;
    std::string line;
    std::cout << "String to insert into list: ";
    std::cin >> userInputString;
    std::getline(std::cin, line);
    for (int i = 0; i < line.length(); i++){
        if (line[i] == ' '){
            std::cout << "Invalid. Can only insert 1 string at a time\n\n";
            return;
        }
    }
    /* ADD CHECK TO ENSURE ONLY INCLUDES CHARS IN INPUT ALPHABET */
    pdaObject.inputStringList.push_back(userInputString);
    std::cout << userInputString << " successfully added to list!!\n\n"; 
    return;
}
void pdaList(){
    /* MAKE A NUMBERED LIST STARTING AT 1 */
    for (auto v : pdaObject.inputStringList)
        std::cout << v << "\n";
    std::cout << "\n";
    return;
}
void pdaOpen(){ // Opens / loads fake config file
    std::cout << "Opening config.txt....\n";
    pdaObject.stateList = {"s0","s1","s2"};
    pdaObject.inputAlphabetList = {'a', 'b'};           
    pdaObject.stackAlphabetList = {'X', 'Y', 'Z'};         
    pdaObject.transitionList.push_back(Transition("s0",'a','X',"s0","XX")); //s0 a X   s0 XX
    pdaObject.transitionList.push_back(Transition("s0",'a','X',"s1","X1")); //s0 a X   s1 X
    pdaObject.transitionList.push_back(Transition("s0",'a','Y',"s0","XY")); //s0 a Y   s0 XY
    pdaObject.transitionList.push_back(Transition("s0",'a','Y',"s1","Y"));  //s0 a Y   s1 Y
    pdaObject.transitionList.push_back(Transition("s0",'a','Z',"s0","XZ")); //s0 a Z   s0 XZ
    pdaObject.transitionList.push_back(Transition("s0",'a','Z',"s1","Z"));  //s0 a Z   s1 Z
    pdaObject.transitionList.push_back(Transition("s0",'b','X',"s0","YX")); //s0 b X   s0 YX
    pdaObject.transitionList.push_back(Transition("s0",'b','X',"s1","X"));  //s0 b X   s1 X
    pdaObject.transitionList.push_back(Transition("s0",'b','Y',"s0","YY")); //s0 b Y   s0 YY
    pdaObject.transitionList.push_back(Transition("s0",'b','Y',"s1","Y"));  //s0 b Y   s1 Y
    pdaObject.transitionList.push_back(Transition("s0",'b','Z',"s0","YZ")); //s0 b Z   s0 YZ
    pdaObject.transitionList.push_back(Transition("s0",'b','Z',"s1","Z")); //s0 b Z   s1 Z
    pdaObject.transitionList.push_back(Transition("s1",'a','X',"s1","\\")); //s1 a X   s1 \'
    pdaObject.transitionList.push_back(Transition("s1",'b','Y',"s1","\\")); //s1 b Y   s1 \'
    pdaObject.transitionList.push_back(Transition("s1",'\\','Z',"s2","\\")); //s1 \ Z   s2 \'              
    pdaObject.initialState = "s0";                          
    pdaObject.startCharacter = 'Z';                        
    pdaObject.finalStateList = {"s2"};
    pdaObject.maximumTransitions = 1;      
    pdaObject.status = NOT_YET_RUN;       
}
void pdaQuit(){
    std::cout << "WORK IN PROGRESS.....\n";
    std::cout << "Quitting push down automata.\n" \
    << "Input string aabba was neither accepted nor rejected in 5 transitions\n\n";
}
void pdaRun(){
    std::cout << "WORK IN PROGRESS.....\n";

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
        pdaObject.status = RUNNING;
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
        std::cout << (*branchItr).remainingInputString << ", ";
        std::cout << (*branchItr).stackToString() << ")\n";
    }
    // do number of transtitions indicated by maximumTransitions on each branch
    int ifThisIsStillZeroAllRejected = 0;
    for (auto b : pdaObject.branchList) {
        int i = pdaObject.maximumTransitions + 1;
        while (i > 0) {
            // check if current state is final state
            for (auto s : pdaObject.finalStateList) {
                if (s == b.currentState) {
                    b.accepted = true;
                    pdaObject.status = NOT_RUNNING;
                    // YAY ACCEPTED print last instantaneous desc.
                    std::cout << "PATH " << b.id << std::endl;
                    std::cout << b.numTransitions << ". (";
                    std::cout << b.currentState << ", ";
                    std::cout << b.remainingInputString << ", ";
                    std::cout << b.stackToString() << ")\n";
                    // print accepted message and return to stop running
                    std::cout << "Input string " << pdaObject.originalInputString;
                    std::cout << " accepted in " << b.numTransitions;
                    std::cout << " transitions!\n\n";
                    return;
                }
            }
            if (i > 1 && b.rejected == false) {
                // find applicable transitions
                //std::cout << "searching transitions for b" << b.id << "...\n"; // for testing
                std::list<Transition> possibleTransitions;
                for (auto t : pdaObject.transitionList) {
                    if (t.startState == b.currentState &&
                        t.startInput == b.remainingInputString.at(0) &&
                        t.startChar == b.currentStack.top()) {
                        //std::cout << "found one t\n"; // for testing
                        possibleTransitions.push_back(t);
                    }
                }
                // if found, update
                if (!possibleTransitions.empty()) {
                    ifThisIsStillZeroAllRejected++;

                    // some updates and copies in case of branching:
                    // update remaining string in a temp value
                    std::string tempStr = b.remainingInputString;
                    tempStr.erase(tempStr.begin());
                    if (tempStr == "") {
                        tempStr = "\\"; // char the represents empty string
                    }
                    // edit numTransitions in temp
                    int tempNum = b.numTransitions+1;
                    // make copy of stack
                    std::stack<char> tempStk = b.currentStack;
                    // make copy of path
                    std::string tempPath = b.path;

                    std::list<Transition>::iterator tItr;
                    int counter = 0;
                    for (tItr = possibleTransitions.begin(); tItr != possibleTransitions.end(); tItr++) {
                        if (counter == 0) {
                            // update current branch's...
                            // state
                            b.currentState = (*tItr).endState;
                            // stack
                            if ((*tItr).endChar == "\\") {
                                b.currentStack.pop();
                            } else if ((*tItr).endChar != (std::string(1,(*tItr).startChar))) {
                                b.currentStack.push((*tItr).endChar.at(0));
                            }
                            // remaining string
                            b.remainingInputString = tempStr;
                            // number of transtitions
                            b.numTransitions = tempNum;
                            // path string
                            b.path = tempPath + "->" + b.currentState;
                        } else {
                            // create new branch to match transition with
                            // its own currentStack and updated path
                            std::stack<char> thisStack = tempStk;
                            if ((*tItr).endChar == "\\") {
                                thisStack.pop();
                            } else if ((*tItr).endChar != (std::string(1,(*tItr).startChar))) {
                                thisStack.push((*tItr).endChar.at(0));
                            }
                            std::string thisPath = tempPath + "->" + (*tItr).endState;
                            Branch newBranch = Branch(pdaObject.branchList.size()+1, (*tItr).endState, tempStr, thisStack, tempNum, thisPath);
                            pdaObject.branchList.push_back(newBranch);
                        }
                        counter++;
                    }
                } else {
                    //std::cout << "b" << b.id << " rejected\n"; // for testing
                    b.rejected = true;
                }

                // check if already at rejection point
                possibleTransitions.clear();
                for (auto t : pdaObject.transitionList) {
                    if (t.startState == b.currentState &&
                        t.startInput == b.remainingInputString.at(0) &&
                        t.startChar == b.currentStack.top()) {
                        possibleTransitions.push_back(t);
                    }
                }
                bool finalState = false;
                for (auto s : pdaObject.finalStateList) {
                    if (s == b.currentState) {
                        finalState = true;
                    }
                }
                if (possibleTransitions.empty() && !finalState) {
                    b.rejected = true;
                }
            }
            i--;
        }
        // print most recent instantaneous description
        if (b.numTransitions != 0) {
            std::cout << "PATH " << b.id << std::endl;
            std::cout << b.numTransitions << ". (";
            std::cout << b.currentState << ", ";
            std::cout << b.remainingInputString << ", ";
            std::cout << b.stackToString() << ")\n";
        }
    }
    if (ifThisIsStillZeroAllRejected == 0) {
        pdaObject.status = NOT_RUNNING;
        // find max num transitions in branches
        int totalTransitions = 0;
        for (auto b : pdaObject.branchList) {
            if (b.numTransitions > totalTransitions) {
                totalTransitions = b.numTransitions;
            }
        }
        // print rejected message
        std::cout << "Input string " << pdaObject.originalInputString;
        std::cout << " rejected in " << totalTransitions;
        std::cout << " transitions!\n\n";
    }
    return;
}
void pdaSet(){
    int userInputTransitions;
    std::string line;
    std::cout << "Number of transitions["<< pdaObject.maximumTransitions<<"]: ";
    std::cin >> userInputTransitions;
    std::getline(std::cin, line);
    for (int i = 0; i < line.length(); i++){
        if (line[i] == ' '){
            std::cout << "Invalid. 1 number at a time\n\n";
            return;
        }
    }
    if (std::cin.fail()){
            std::cout << "Invalid number of transitions\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
    }
    // added check to ensure num is positive
    if (userInputTransitions < 1) {
        std::cout << "Invalid. Must be greater than or equal to 1\n\n";
        return;
    }
    pdaObject.maximumTransitions = userInputTransitions;
    std::cout << "Set maximum transitions to " << pdaObject.maximumTransitions << "\n\n";
    return;
}
void pdaShow(){
    std::cout << "WORK IN PROGRESS.....\n";
    std::cout \
    << "Course:                   "<< "Cpts 422" << '\n'\
    << "Semester:                 "<< "Fall" << '\n'\
    << "Year:                     "<< "2020" << '\n'\
    << "Instructor:               "<< "Luis DeLatorre" << '\n'\
    << "Authors:                  "<< "Group" << '\n'\
    << "Version:                  "<< "Prototype v2" << '\n';
    std::cout << "(CFG)Transitions Allowed: "<< pdaObject.maximumTransitions << '\n';
    std::cout << "(CFG)Maximum Cells:        "<< 32 << '\n';
    std::cout << "Turing Machine Name:      "<< "Prototype v2" << '\n';
    std::cout << "Turing Machine Status:    "<< pdaObject.status << '\n'\
    << "Input Strings Status:     "<< "No changes made"<< '\n' \
    << "Current Input String:     "<< "aba" << '\n' \
    << "Total Transitions:        "<< "0"     << '\n';
}
void pdaView(){
    /* ADD COUT FOR PDA DESCRIPTION IF NOT NULL */
    std::cout << "STATES: ";
    for (auto v : pdaObject.stateList)
        std::cout << v << " ";
    std::cout << "\n\n";
    std::cout << "INPUT_ALPHABET: ";
    for (auto v : pdaObject.inputAlphabetList)
        std::cout << v << " ";
    std::cout << "\n\n";
    std::cout << "STACK_ALPHABET: ";
    for (auto v : pdaObject.stackAlphabetList)
        std::cout << v << " ";
    std::cout << "\n\n";
    std::cout << "TRANSITION_FUNCTION:\n";
    for (auto it = pdaObject.transitionList.cbegin(); it != pdaObject.transitionList.cend(); it++){
        std::cout << it->startState << " " << it->startInput << " " << it->startChar << "  " << it->endState << " " << it->endChar << "\n";
    }
    std::cout << "\n\n";
    std:: cout << "INITIAL_STATE: " << pdaObject.initialState;
    std::cout << "\n\n";

    std::cout << "START_CHARACTER: " << pdaObject.startCharacter;
    std::cout << "\n\n";

    std::cout << "FINAL_STATES: " ;
    for (auto v : pdaObject.finalStateList)
        std::cout << v << " ";
    std::cout << "\n\n";
}
// ******************************************************
