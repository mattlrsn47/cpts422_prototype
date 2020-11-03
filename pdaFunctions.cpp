#include "pdaHeader.h"

void pdaClose(){
    std::cout << "Succeeded in writing list to myPDA.str!\n\n";
}

void pdaDisplay(){
    std::cout       << "This function displays complete paths.\n"   \
                    << "1. s0 -> s1\n" \
                    << "2. s1 -> s2\n" \
                    << "3. s2 -> s4\n" \
                    << "4. s4 -> s0\n" \
                    << "5. s0 -> s0\n\n";
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
    std::cout << "String to insert into List: aabba \n" \
    << "Inserted aabba to list.\n\n";
    return;
}
void pdaList(){
    std::cout \
    << "1. aabba\n" \
    << "2. aba\n"  \
    << "3. aabbb\n"  \
    << "4. aaabb\n\n";
    return;
}
void pdaOpen(){
    std::cout << "Opening push down automata..\n"\
    << "PDA Name: myPDA\n"\
    << "Successfully loaded!\n\n";
}
void pdaQuit(){
    std::cout << "Quitting push down automata.\n" \
    << "Input string aabba was neither accepted nor rejected in 5 transitions\n\n";
}
void pdaRun(){
    std::cout << "Running pda\n";
    std::cout << "0. " << "[s0]aabba\n"\
    << "1. x[s1]aabb\n"\
    << "2. xy[s2]aab\n"\
    << "3. xyx[s4]aa\n"\
    << "4. xyxx[s0]a\n"\
    << "5. xyxxy[s0]\n";
    std::cout << "string aabba accepted in 5 transition(s)\n";
    return;
}
void pdaSet(){
    std::cout \
    << "Set the number of max transitions to: 5\n" \
    << "Maximum transitions set to 5\n\n" ;
}
void pdaShow(){
    std::cout \
    << "Course:                   "<< "Cpts 422" << '\n'\
    << "Semester:                 "<< "Fall" << '\n'\
    << "Year:                     "<< "2020" << '\n'\
    << "Instructor:               "<< "Luis DeLatorre" << '\n'\
    << "Authors:                  "<< "Group" << '\n'\
    << "Version:                  "<< "Prototype" << '\n'\
    << "(CFG)Transitions Allowed: "<< "5" << '\n'\
    << "(CFG)Maximum Cells:        "<< "32" << '\n'\
    << "Turing Machine Name:      "<< "Prototype" << '\n'\
    << "Turing Machine Status:    "<< "Running" << '\n'\
    << "Input Strings Status:     "<< "No changes made"<< '\n' \
    << "Current Input String:     "<< "aabba" << '\n' \
    << "Total Transitions:        "<< "0"     << '\n';
}
void pdaView(){
    std::cout << "" \

    << "This PDA accepts the language of odd palindromes over {a, b} is shown below. Any transition not specified in this pushdown automaton is empty.\n\n" \
    << "STATES: s0 s1 s2\n\n"  \

    << "INPUT_ALPHABET: a b\n\n" \

    << "STACK_ALPHABET: X Y Z\n\n" \

    << "TRANSITION_FUNCTION:\n" \
    <<"s0 a X   s0 XX \n"\
    <<"s0 a X   s1 X\n"\
    <<"s0 a Y   s0 XY\n"\
    <<"s0 a Y   s1 Y\n"\
    <<"s0 a Z   s0 XZ\n"\
    <<"s0 a Z   s1 Z\n"\
    <<"s0 b X   s0 YX\n"\
    <<"s0 b X   s1 X\n"\
    <<"s0 b Y   s0 YY\n"\
    <<"s0 b Y   s1 Y\n"\
    <<"s0 b Z   s0 YZ\n"\
    <<"s0 b Z   s1 Z\n"\
    <<"s1 a X   s1 '\'\n"\
    <<"s1 b Y   s1 '\' \n"\
    <<"s1 '\' Z   s2 '\' \n\n"\

    << "INITIAL_STATE: s0\n\n"\

    << "START_CHARACTER: Z\n\n"\

    << "FINAL_STATES: s2\n\n";
    }


// ******************************************************
