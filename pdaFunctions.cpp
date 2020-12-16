#include "pdaHeader.h"
#include "UIHeader.h"


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
                std::cout << "String is already in list!\n\n";
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
        std::cout << "No PDA is open to list input strings!\n\n";
    }
    return;
}


void pdaQuit(){
    if (pdaObject.open) {
        if (pdaObject.status != RUNNING) {
            std::cout << "The PDA was not running!\n\n";
            return;
        } else {
            std::cout << "Quitting...\n" \
            << "Input string " << pdaObject.originalInputString << " was neither accepted nor rejected in " << pdaObject.totalTransitions << " transitions\n\n";
            pdaObject.status = NOT_RUNNING;
        }
    } else {
        std::cout << "No PDA is open to quit!\n\n";
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
