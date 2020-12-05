#ifndef __CONFIGURATION__
#define __CONFIGURATION__
#include <fstream>
#include <iostream>
#include <ctype.h>
#include <string>
class pdaConfig
{
private:
    int maximum_number_of_characters;
    int maximum_number_of_transitions;
public:
    pdaConfig();
    ~pdaConfig();
    void load(std::ifstream configuration);
    void update_maximum_number_of_transitions(int new_setting);//setter for maximum_number_of_transitions
    void update_maximum_number_of_characters(int new_setting);//setter for maximum_number_of_characters
};
#endif
