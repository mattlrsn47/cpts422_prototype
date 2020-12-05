#include "pdaHeader.h"
#include <limits>  

/******* Class functions ******/

//          PDA
class PdaObject{
public:
    /* definition and config */
    std::list<std::string> stateList;                   // STATES:
    std::list<std::string> inputAlphabetList;           // INPUT_ALPHABET:    
    std::list<std::string> stackAlphabetList;           // STACK_ALPHABET:
    std::list<Transition> transitionList;               // TRANSITION_FUNCTION:
    std::string initialState;                           // INITIAL_STATE:      
    std::string startCharacter;                         // START_CHARACTER:
    std::list<std::string> finalStateList;              // FINAL_STATES:

    std::list<std::string> inputStringList;
    int maximumTransitions;
    std::string status;  /* running or not running */
    PdaObject(/* args */);
    ~PdaObject();
}pdaObject;

PdaObject::PdaObject(/* args */){
}

PdaObject::~PdaObject(){
}
//          TRANSITION
Transition::Transition(std::string ss, std::string si, std::string sc, std::string es, std::string ec){
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
    std::cout << "WORK IN PROGRESS.....\n";
    std::cout       << "This function displays complete paths.\n"   \
                    << "Path1. s0->s0->s1\n" \
                    << "Path2. s0->s0->s1->s0\n" \
                    << "Path3. s0->s0->s1->s1\n" \
                    << "Path4. s0->s0->s1->s1->s2\n\n";
                

                   
}

void pdaExit(){
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
    pdaObject.inputStringList.push_back(userInputString);
    std::cout << userInputString << " successfully added to list!!\n\n"; 
    return;
}
void pdaList(){
    for (auto v : pdaObject.inputStringList)
        std::cout << v << "\n";
    return;
}
void pdaOpen(){ // Opens / loads fake config file
    std::cout << "Opening config.txt....\n";
    pdaObject.stateList = {"s0","s1","s2"};
    pdaObject.inputAlphabetList = {"a", "b"};           
    pdaObject.stackAlphabetList = {"X", "Y", "Z"};         
    pdaObject.transitionList.push_back(Transition("s0","a","X","s0","XX")); //s0 a X   s0 XX
    pdaObject.transitionList.push_back(Transition("s0","a","X","s1","X1")); //s0 a X   s1 X
    pdaObject.transitionList.push_back(Transition("s0","a","Y","s0","XY")); //s0 a Y   s0 XY
    pdaObject.transitionList.push_back(Transition("s0","a","Y","s1","Y"));  //s0 a Y   s1 Y
    pdaObject.transitionList.push_back(Transition("s0","a","Z","s0","XZ")); //s0 a Z   s0 XZ
    pdaObject.transitionList.push_back(Transition("s0","a","Z","s1","Z"));  //s0 a Z   s1 Z
    pdaObject.transitionList.push_back(Transition("s0","b","X","s0","YX")); //s0 b X   s0 YX
    pdaObject.transitionList.push_back(Transition("s0","b","X","s1","X"));  //s0 b X   s1 X
    pdaObject.transitionList.push_back(Transition("s0","b","Y","s0","YY")); //s0 b Y   s0 YY
    pdaObject.transitionList.push_back(Transition("s0","b","Y","s1","Y"));  //s0 b Y   s1 Y
    pdaObject.transitionList.push_back(Transition("s0","b","Z","s0","YZ")); //s0 b Z   s0 YZ
    pdaObject.transitionList.push_back(Transition("s0","b","Z","s1","Z")); //s0 b Z   s1 Z
    pdaObject.transitionList.push_back(Transition("s1","a","X","s1","\\")); //s1 a X   s1 \'
    pdaObject.transitionList.push_back(Transition("s1","b","Y","s1","\\")); //s1 b Y   s1 \'
    pdaObject.transitionList.push_back(Transition("s1","\\","Z","s2","\\")); //s1 \ Z   s2 \'              
    pdaObject.initialState = {"s0"};                          
    pdaObject.startCharacter = "Z";                        
    pdaObject.finalStateList = {"s2"};
    pdaObject.maximumTransitions = 1;      
    pdaObject.status = "not running";       
}
void pdaQuit(){
    std::cout << "WORK IN PROGRESS.....\n";
    std::cout << "Quitting push down automata.\n" \
    << "Input string aabba was neither accepted nor rejected in 5 transitions\n\n";
}
void pdaRun(){
    std::cout << "WORK IN PROGRESS.....\n";
    
    std::cout << "Running pda\n";
    std::cout \
    << "0. z[s0]aba\n"\
    << "1. xz[s0]ba\n"\
    
    << "2. yxz[s0]a\n"\
    << "   xz[s1]a\n"\
    
    << "3. xyxz[s0]\n"\
    << "   yxz[s1]\n"\

    << "   \\xz[s1]\n"\
    
    << "4. xz[s2]\n"\
    << "\n";

    std::cout << "string aba accepted in 4 transition(s)\n";
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
