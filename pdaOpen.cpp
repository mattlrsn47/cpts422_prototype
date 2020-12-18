#include "pdaHeader.h"

void pdaOpen(std::ostream &output, std::istream &input){
    if (pdaObject.open) {
        output << "A PDA is already open! Please close it first.\n\n";
        return;
    }
    std::string pdaName;
    std::string line;
    output << "Name of PDA to open: ";
    input >> pdaName;

    /* defintion file */
    pdaObject.name = "";
    output << "Opening " << pdaName << ".def...\n";
    std::ifstream definition(pdaName + ".def");
    if (!definition.is_open()) {
        output << "Invalid definition file!\n\n";
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
                        output << "Illegal states. Invalid definition!\n\n";
                        return;
                    }
                }
            }
            // check if duplicate state
            for (auto st : pdaObject.stateList) {
                if (st == state) {
                    output << "Illegal states. Invalid definition!\n\n";
                    return;
                }
            }
            pdaObject.stateList.push_back(state);
        }
    }
    if ((!(definition >> value)) || (value != "INPUT_ALPHABET:")) {
        output << "Missing keyword after states. Invalid definition!\n\n";
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
                        output << "Illegal input alphabet. Invalid definition!\n\n";
                        return;
                    }
                }
                pdaObject.inputAlphabetList.push_back(item[0]);
            } else {
                output << "Illegal input alphabet. Invalid definition!\n\n";
                return;
            }
        }
    } else {
        output << "Illegal input alphabet. Invalid definition!\n\n";
        return;
    }
    if ((!(definition >> value)) || (value != "STACK_ALPHABET:")) {
        output << "Missing keyword after input alphabet. Invalid definition!\n\n";
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
                        output << "Illegal stack alphabet. Invalid definition!\n\n";
                        return;
                    }
                }
                pdaObject.stackAlphabetList.push_back(item[0]);
            } else {
                output << "Illegal stack alphabet. Invalid definition!\n\n";
                return;
            }
        }
    } else {
        output << "Illegal stack alphabet. Invalid definition!\n\n";
        return;
    }
    if ((!(definition >> value)) || (value != "TRANSITION_FUNCTION:")) {
        output << "Missing keyword after stack alphabet. Invalid definition!\n\n";
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
            output << "Illegal transition function. Invalid definition!\n\n";
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
        output << "Illegal initial state. Invalid definition!\n\n";
        return;
    }
    if ((!(definition >> value)) || value != "START_CHARACTER:") {
        output << "Missing keyword after initial state. Invalid definition!\n\n";
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
            output << "Illegal start character. Invalid definition!\n\n";
            return;
        }
    } else {
        output << "Illegal start character. Invalid definition!\n\n";
        return;
    }
    if ((!(definition >> value)) || (value != "FINAL_STATES:")) {
        output << "Missing keyword after start character. Invalid definition!\n\n";
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
                        output << "Illegal final states. Invalid definition!\n\n";
                        return;
                    }
                }
            }
            // check if duplicate final state
            for (auto st : pdaObject.finalStateList) {
                if (st == state) {
                    output << "Illegal final states. Invalid definition!\n\n";
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
                output << "Illegal final states. Invalid definition!\n\n";
                return;
            }
        }
    } else {
        output << "Illegal final states. Invalid definition!\n\n";
        return;
    }

    definition.close();

    /* input string file */
    pdaObject.stringListChanged = false;
    pdaObject.inputStringList.clear();
    output << "Opening " << pdaName << ".str...\n";
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
            output << "Input string \"" << line << "\" discarded.\n";
            pdaObject.stringListChanged = true;
        }
    }

    inputStrings.close();

    /* config file */
    pdaObject.maximumTransitions = 1;
    pdaObject.maximumCharacters = 32;

    output << "Opening " << pdaName << ".cfg...\n";
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
   
    output << "\n";
    pdaObject.accepted = false;
    pdaObject.rejected = false;
    pdaObject.status = NOT_YET_RUN;
    pdaObject.totalTransitions = 0;    
    pdaObject.open = true;   
}