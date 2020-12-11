#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <stack>
#define DELETE

/* PDA Status Values */
#define RUNNING 2
#define NOT_RUNNING 1
#define NOT_YET_RUN 0

/******* Class Definitions ******/

//          TRANSITION
class Transition{
public:
    std::string startState;
    char startInput;
    char startChar;

    std::string endState;
    std::string endChar;
    Transition(std::string ss, char si, char sc, std::string es, std::string ec);
    ~Transition();
};

//          BRANCH
// if more than one transition is applicable, pda creates one branch per additional transition
class Branch {
public:
    int id;
    std::string currentState;
    std::string remainingInputString; // should update after each transition
    std::stack<char> currentStack;
    bool accepted; // starts as false
    bool rejected; // starts as false
    int numTransitions;
    std::string path;
    std::string stackToString(int maxChar);
    Branch(int branchId, std::string cstate, std::string ris, std::stack<char> cstack, int nt, std::string p);
    ~Branch();
};

//          PDAOBJECT
class PdaObject{
public:
    bool open;
    /* definition file */
    std::string name;
    std::string description;                            // possible desc.
    std::list<std::string> stateList;                   // STATES:
    std::list<char> inputAlphabetList;                  // INPUT_ALPHABET:    
    std::list<char> stackAlphabetList;                  // STACK_ALPHABET:
    std::list<Transition> transitionList;               // TRANSITION_FUNCTION:
    std::string initialState;                           // INITIAL_STATE:      
    char startCharacter;                                // START_CHARACTER:
    std::list<std::string> finalStateList;              // FINAL_STATES:
    /* string file */
    std::list<std::string> inputStringList;
    bool stringListChanged;
    /* config file */
    int maximumTransitions;
    int maximumCharacters;

    /* for running */
    int status;  // 2=running, 1=not running, 0=not yet run
    std::string originalInputString;
    std::list<Branch> branchList;   // to track multiple paths
    int totalTransitions;

    PdaObject(/* args */);
    ~PdaObject();
}pdaObject;