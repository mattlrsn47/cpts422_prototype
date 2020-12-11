#include "pdaHeader.h"
#include "UIHeader.h"
#include <limits>
#include <fstream>  
#include <sstream>

/******* Class functions ******/

//          PDAOBJECT
PdaObject::PdaObject(){
    open = false;
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
}

Branch::~Branch(){

}

std::string Branch::stackToString(int maxChar){
    std::stack<char> temp = currentStack;
    std::string stringStack;
    while (!temp.empty() && maxChar != 0) {
        stringStack.push_back(temp.top());
        temp.pop();
        maxChar--;
    }
    if (!temp.empty()) {
        // truncated stack
        stringStack.push_back('>');
    }
    return stringStack;
}

std::string Branch::truncateInputString(int maxChar){
    std::string temp = "";
    if (remainingInputString.length() > maxChar) {
        for (int i = 0; i < maxChar; i++) {
            temp.push_back(remainingInputString[i]);
        }
        temp.push_back('>');
    } else {
        temp = remainingInputString;
    }
    return temp;
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
    if (pdaObject.open) {
        std::cout << "Closing PDA....\n\n";
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
                std::cout << "Failed to write input strings to " << pdaObject.name << ".str\n";
            }
            std::cout << "Succeeded in writing input strings to " << pdaObject.name << ".str\n\n";
        }
        pdaObject = PdaObject(); // reset pda object
    } else {
        std::cout << "No PDA was open!\n\n";
    }
    return;
}

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
        std::cout << "No PDA is open to display!";
    }
    return;
}

void pdaExit(){
    /* if PDA open, call pdaClose() */
    if (pdaObject.open) {
        pdaClose();
    }
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
    if (pdaObject.open) {
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
        /* ensure string only includes chars from input alphabet */
        int numValidChar = 0;
        for (auto c : userInputString) {
            for (auto a : pdaObject.inputAlphabetList) {
                if (c == a) {
                    numValidChar++;
                }
            }
        }
        if (numValidChar != userInputString.length()) {
            std::cout << "Invalid character in string!\n\n";
            return;
        }
        // check if duplicate string
        for (auto s : pdaObject.inputStringList) {
            if (s == userInputString) {
                std::cout << "String is already in list!";
                return;
            }
        }
        pdaObject.inputStringList.push_back(userInputString);
        pdaObject.stringListChanged = true;
        std::cout << userInputString << " successfully added to list!\n\n";
    } else {
        std::cout << "No PDA is open to add input strings for!\n\n";
    } 
    return;
}

void pdaList(){
    if (pdaObject.open) {
        int i = 1;
        for (auto v : pdaObject.inputStringList) {
            std::cout << i << ". " << v << "\n";
            i++;
        }
        std::cout << "\n";
    } else {
        std::cout << "No PDA is open to list input strings!";
    }
    return;
}

void pdaOpen(){
    if (pdaObject.open) {
        std::cout << "A PDA is already open! Please close it first.\n\n";
        return;
    }
    std::string pdaName;
    std::string line;
    std::cout << "Name of PDA to open: ";
    std::cin >> pdaName;

    /* defintion file */
    pdaObject.name = "";
    std::cout << "Opening " << pdaName << ".def...\n";
    std::ifstream definition(pdaName + ".def");
    if (!definition.is_open()) {
        std::cout << "Invalid definition file!\n\n";
        return;
    }
    pdaObject.name = pdaName;

    // get description
    pdaObject.description.clear();
    std::string value;
    definition >> value;
    while (value != "STATES:") {
        pdaObject.description.push_back(value);
        definition >> value;
    }
    
    // get states
    pdaObject.stateList.clear();
    if (getline(definition, value)) {
        std::istringstream iss(value);
        std::string state;
        while (iss >> state) {
            // check that state name is alpha-numeric (with underscores)
            for (int i = 0; i < state.length(); i++) {
                if (!isalnum(state[i])) {
                    if (state[i] != '_') {
                        std::cout << "Illegal states. Invalid definition!\n\n";
                        return;
                    }
                }
            }
            // check if duplicate state
            for (auto st : pdaObject.stateList) {
                if (st == state) {
                    std::cout << "Illegal states. Invalid definition!\n\n";
                    return;
                }
            }
            pdaObject.stateList.push_back(state);
        }
    }
    if ((!(definition >> value)) || (value != "INPUT_ALPHABET:")) {
        std::cout << "Missing keyword after states. Invalid definition!\n\n";
        return;
    }

    // get input alphabet
    pdaObject.inputAlphabetList.clear();
    if (getline(definition, value)) {
        std::istringstream iss(value);
        std::string item;
        while (iss >> item) {
            // check that item's a single char and not a reserved char
            if ((item.length() == 1) && (item[0] != '\\') &&
                (item[0] != '(') && (item[0] != ')') &&
                (item[0] != ',') && (item[0] != '>') && 
                (item[0] >= '!') && (item[0] <= '~')) {
                // check if duplicate item
                for (auto a : pdaObject.inputAlphabetList) {
                    if (a == item[0]) {
                        std::cout << "Illegal input alphabet. Invalid definition!\n\n";
                        return;
                    }
                }
                pdaObject.inputAlphabetList.push_back(item[0]);
            } else {
                std::cout << "Illegal input alphabet. Invalid definition!\n\n";
                return;
            }
        }
    } else {
        std::cout << "Illegal input alphabet. Invalid definition!\n\n";
        return;
    }
    if ((!(definition >> value)) || (value != "STACK_ALPHABET:")) {
        std::cout << "Missing keyword after input alphabet. Invalid definition!\n\n";
        return;
    }

    // get stack alphabet
    pdaObject.stackAlphabetList.clear();
    if (getline(definition, value)) {
        std::istringstream iss(value);
        std::string item;
        while (iss >> item) {
            // check that item's a single char and not a reserved char
            if ((item.length() == 1) && (item[0] != '\\') &&
                (item[0] != '(') && (item[0] != ')') &&
                (item[0] != ',') && (item[0] != '>') && 
                (item[0] >= '!') && (item[0] <= '~')) {
                // check if duplicate item
                for (auto a : pdaObject.stackAlphabetList) {
                    if (a == item[0]) {
                        std::cout << "Illegal stack alphabet. Invalid definition!\n\n";
                        return;
                    }
                }
                pdaObject.stackAlphabetList.push_back(item[0]);
            } else {
                std::cout << "Illegal stack alphabet. Invalid definition!\n\n";
                return;
            }
        }
    } else {
        std::cout << "Illegal stack alphabet. Invalid definition!\n\n";
        return;
    }
    if ((!(definition >> value)) || (value != "TRANSITION_FUNCTION:")) {
        std::cout << "Missing keyword after stack alphabet. Invalid definition!\n\n";
        return;
    }

    // get transitions
    pdaObject.transitionList.clear();
    std::string startState;
    char startInput;
    char startChar;
    std::string endState;
    std::string endChar;
    while (definition >> startState) {
        if (startState == "INITIAL_STATE:") {
            break;
        }
        definition >> startInput;
        definition >> startChar;
        definition >> endState;
        definition >> endChar;
        // validate transition uses valid chars & states
        bool validStartState = false;
        bool validStartInput = false;
        bool validStartChar = false;
        bool validEndState = false;
        bool validEndChar = false;
        for (auto st : pdaObject.stateList) {
            if (st == startState) {
                validStartState = true;
            }
            if (st == endState) {
                validEndState = true;
            }
        }
        for (auto ia : pdaObject.inputAlphabetList) {
            if (ia == startInput) {
                validStartInput = true;
            }
        }
        if (startInput == '\\') {
            validStartInput = true;
        }
        int checkEachChar = 0;
        for (auto sa : pdaObject.stackAlphabetList) {
            if (sa == startChar) {
                validStartChar = true;
            }
            for (int i = 0; i < endChar.length(); i++) {
                if (sa == endChar[i]) {
                    checkEachChar++;
                }
            }
        }
        if (endChar == "\\") {
            checkEachChar++;
        }
        if (checkEachChar == endChar.length()) {
            validEndChar = true;
        }
        if (validStartState && validStartInput && validStartChar &&
            validEndState && validEndChar) {
            Transition newT = Transition(startState, startInput, startChar, endState, endChar);
            pdaObject.transitionList.push_back(newT);
        } else {
            std::cout << "Illegal transition function. Invalid definition!\n\n";
            return;
        }
    }

    // get initial state
    pdaObject.initialState = "";
    definition >> value;
    // validate initial state is part of states
    bool validInitialState = false;
    for (auto st : pdaObject.stateList) {
        if (st == value) {
            validInitialState = true;
        }
    }
    if (validInitialState) {
        pdaObject.initialState = value;
    } else {
        std::cout << "Illegal initial state. Invalid definition!\n\n";
        return;
    }
    if ((!(definition >> value)) || value != "START_CHARACTER:") {
        std::cout << "Missing keyword after initial state. Invalid definition!\n\n";
        return;
    }

    // get start char
    pdaObject.startCharacter = '\0';
    if ((definition >> value) && (value.length() == 1) &&
        (value[0] != '\\') && (value[0] != '(') &&
        (value[0] != ')') && (value[0] != ',') &&
        (value[0] != '>') && (value[0] >= '!') &&
        (value[0] <= '~')) {
        // validate start character is in stack alphabet
        bool validStartChar = false;
        for (auto a : pdaObject.stackAlphabetList) {
            if (a == value[0]) {
                validStartChar = true;
            }
        }
        if (validStartChar) {
            pdaObject.startCharacter = value[0];
        } else {
            std::cout << "Illegal start character. Invalid definition!\n\n";
            return;
        }
    } else {
        std::cout << "Illegal start character. Invalid definition!\n\n";
        return;
    }
    if ((!(definition >> value)) || (value != "FINAL_STATES:")) {
        std::cout << "Missing keyword after start character. Invalid definition!\n\n";
        return;
    }

    // get final states
    pdaObject.finalStateList.clear();
    if (getline(definition, value)) {
        std::istringstream iss(value);
        std::string state;
        while (iss >> state) {
            // check that state name is alpha-numeric (with underscores)
            for (int i = 0; i < state.length(); i++) {
                if (!isalnum(state[i])) {
                    if (state[i] != '_') {
                        std::cout << "Illegal final states. Invalid definition!\n\n";
                        return;
                    }
                }
            }
            // check if duplicate final state
            for (auto st : pdaObject.finalStateList) {
                if (st == state) {
                    std::cout << "Illegal final states. Invalid definition!\n\n";
                    return;
                }
            }
            // validate final state is part of states
            bool validFinalState = false;
            for (auto st : pdaObject.stateList) {
                if (st == state) {
                    validFinalState = true;
                }
            }
            if (validFinalState) {
                pdaObject.finalStateList.push_back(state);
            } else {
                std::cout << "Illegal final states. Invalid definition!\n\n";
                return;
            }
        }
    } else {
        std::cout << "Illegal final states. Invalid definition!\n\n";
        return;
    }

    definition.close();

    /* input string file */
    pdaObject.stringListChanged = false;
    pdaObject.inputStringList.clear();
    std::cout << "Opening " << pdaName << ".str...\n";
    std::ifstream inputStrings(pdaName + ".str");
    //std::string line;
    while (getline(inputStrings, line)) {
        // validate input string on line
        bool validLine = false;
        if (line == "\\") {
            validLine = true;
        } else {
            if (line.length() > 0) {
                int checkEachChar = 0;
                for (int i = 0; i < line.length(); i++) {
                    for (auto a : pdaObject.inputAlphabetList) {
                        if (a == line[i]) {
                            checkEachChar++;
                        }
                    }
                }
                if (checkEachChar == line.length()) {
                    validLine = true;
                }
            }
        }
        if (validLine) {
            // check if duplicate string
            for (auto s : pdaObject.inputStringList) {
                if (s == line) {
                    validLine = false;
                }
            }
        }
        if (validLine) {
            pdaObject.inputStringList.push_back(line);
        } else {
            std::cout << "Input string \"" << line << "\" discarded.\n";
            pdaObject.stringListChanged = true;
        }
    }

    inputStrings.close();

    /* config file */
    pdaObject.maximumTransitions = 1;
    pdaObject.maximumCharacters = 32;

    std::cout << "Opening " << pdaName << ".cfg...\n";
    std::ifstream config(pdaName + ".cfg");
    config >> value;
    if (value == "MAXIMUM_TRANSITIONS=") {
        config >> value;
        if (stoi(value) >= 1) {
            pdaObject.maximumTransitions = stoi(value);
        }
    }
    config >> value;
    if (value == "MAXIMUM_CHARACTERS=") {
        config >> value;
        if (stoi(value) >= 1) {
            pdaObject.maximumCharacters = stoi(value);
        }
    }

    config.close();
   
    std::cout << "\n";
    pdaObject.status = NOT_YET_RUN;
    pdaObject.totalTransitions = 0;    
    pdaObject.open = true;   
}

void pdaQuit(){
    if (pdaObject.open) {
        if (pdaObject.status != RUNNING) {
            std::cout << "The PDA was not running!\n\n";
            return;
        } else {
            std::cout << "Quitting...\n" \
            << "Input string " << pdaObject.originalInputString << " was neither accepted nor rejected in " << pdaObject.totalTransitions << " transitions\n\n";
        }
    } else {
        std::cout << "No PDA is open to quit!\n\n";
    }
    return;
}

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
        pdaObject.status = NOT_RUNNING;
        std::cout << "Input string " << pdaObject.originalInputString;
        std::cout << " rejected in " << pdaObject.totalTransitions;
        std::cout << " transitions!\n\n";
    }
    return;
}

void pdaSet(){
    if (!pdaObject.open) {
        std::cout << "No PDA is open to change settings!\n\n";
        return;
    }
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

void pdaView(){
    if (pdaObject.open) {
        if (!pdaObject.description.empty()) {
            for (auto v : pdaObject.description) {
                std::cout << v << " ";
            }
            std::cout << "\n\n";
        }
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
    } else {
        std::cout << "No PDA is open to view!\n\n";
    }
    return;
}
// ******************************************************
