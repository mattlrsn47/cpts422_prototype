#include "pdaConfig.h"
pdaConfig::pdaConfig()
{//default values for the config
    maximum_number_of_characters = 32;
    maximum_number_of_transitions = 1;
}

pdaConfig::~pdaConfig()
{
}


void pdaConfig::load(std::ifstream configuration)
{
    std::string inputLine, configKeyword;
    int newConfigValue, equalSignLoc;
    if (configuration.is_open())
    {
        configuration >> inputLine;//gets the a line in the file
        equalSignLoc = inputLine.find('=');//finds  where the equal sign that sepeates the keyword from the value is
        configKeyword = inputLine.substr(0, equalSignLoc - 1);//grabs the keyword 
        newConfigValue = atoi(inputLine.substr(equalSignLoc + 1).c_str());//grabs the value
        if (!configKeyword.compare("MAXIMUM_TRANSITIONS"))
        {
            update_maximum_number_of_transitions(newConfigValue);
        }
        else if (!configKeyword.compare("MAXIMUM_CHARACTERS"))
        {
            update_maximum_number_of_characters(newConfigValue);
        }
    }
    return;
}

void pdaConfig::update_maximum_number_of_transitions(int new_setting)
{
    if (new_setting  >= 1)//makes sure the given value is valid
    {
        maximum_number_of_transitions = new_setting;
    }
    return;    
}
void pdaConfig::update_maximum_number_of_characters(int new_setting)
{
    if (new_setting  >= 1)//makes sure the given value is valid
    {
        maximum_number_of_characters = new_setting;
    }
    return;    
}
