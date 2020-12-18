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
void pdaExit(std::ostream &output){
    /* if PDA open, call pdaClose() */
    if (pdaObject.open) {
        pdaClose(output);
    }
    output << ("Successfully exited application\n\n");
    std::cerr << "Success";
    exit(0);
    return;
}

void pdaHelp(std::ostream &output){
    output \
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

void pdaInsert(std::ostream &output, std::istream &input){
    if (pdaObject.open) {
        std::string userInputString;
        std::string line;
        output << "String to insert into list: ";
        input >> userInputString;
        std::getline(input, line);
        for (int i = 0; i < line.length(); i++){
            if (line[i] == ' '){
                output << "Invalid. Can only insert 1 string at a time\n\n";
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
            output << "Invalid character in string!\n\n";
            return;
        }
        // check if duplicate string
        for (auto s : pdaObject.inputStringList) {
            if (s == userInputString) {
                output << "String is already in list!\n\n";
                return;
            }
        }
        pdaObject.inputStringList.push_back(userInputString);
        pdaObject.stringListChanged = true;
        output << userInputString << " successfully added to list!\n\n";
    } else {
        output << "No PDA is open to add input strings for!\n\n";
    } 
    return;
}

void pdaList(std::ostream &output){
    if (pdaObject.open) {
        int i = 1;
        for (auto v : pdaObject.inputStringList) {
            output << i << ". " << v << "\n";
            i++;
        }
        output << "\n";
    } else {
        output << "No PDA is open to list input strings!\n\n";
    }
    return;
}


void pdaQuit(std::ostream &output){
    if (pdaObject.open) {
        if (pdaObject.status != RUNNING) {
            output << "The PDA was not running!\n\n";
            return;
        } else {
            output << "Quitting...\n" \
            << "Input string " << pdaObject.originalInputString << " was neither accepted nor rejected in " << pdaObject.totalTransitions << " transitions\n\n";
            pdaObject.status = NOT_RUNNING;
        }
    } else {
        output << "No PDA is open to quit!\n\n";
    }
    return;
}

void pdaSet(std::ostream &output, std::istream &input){
    if (!pdaObject.open) {
        output << "No PDA is open to change settings!\n\n";
        return;
    }
    int userInputTransitions;
    std::string line;
    output << "Number of transitions["<< pdaObject.maximumTransitions<<"]: ";
    input >> userInputTransitions;
    std::getline(input, line);
    for (int i = 0; i < line.length(); i++){
        if (line[i] == ' '){
            output << "Invalid. 1 number at a time\n\n";
            return;
        }
    }
    if (std::cin.fail()){
            output << "Invalid number of transitions\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
    }
    // added check to ensure num is positive
    if (userInputTransitions < 1) {
        output << "Invalid. Must be greater than or equal to 1\n\n";
        return;
    }
    pdaObject.maximumTransitions = userInputTransitions;
    output << "Set maximum transitions to " << pdaObject.maximumTransitions << "\n\n";
    return;
}

void pdaView(std::ostream &output){
    if (pdaObject.open) {
        if (!pdaObject.description.empty()) {
            for (auto v : pdaObject.description) {
                output << v << " ";
            }
            output << "\n\n";
        }
        output << "STATES: ";
        for (auto v : pdaObject.stateList)
            output << v << " ";
        output << "\n\n";
        output << "INPUT_ALPHABET: ";
        for (auto v : pdaObject.inputAlphabetList)
            output << v << " ";
        output << "\n\n";
        output << "STACK_ALPHABET: ";
        for (auto v : pdaObject.stackAlphabetList)
            output << v << " ";
        output << "\n\n";
        output << "TRANSITION_FUNCTION:\n";
        for (auto it = pdaObject.transitionList.cbegin(); it != pdaObject.transitionList.cend(); it++){
            output << it->startState << " " << it->startInput << " " << it->startChar << "  " << it->endState << " " << it->endChar << "\n";
        }
        output << "\n\n";
        output << "INITIAL_STATE: " << pdaObject.initialState;
        output << "\n\n";

        output << "START_CHARACTER: " << pdaObject.startCharacter;
        output << "\n\n";

        output << "FINAL_STATES: " ;
        for (auto v : pdaObject.finalStateList)
            output << v << " ";
        output << "\n\n";
    } else {
        output << "No PDA is open to view!\n\n";
    }
    return;
}
// ******************************************************
