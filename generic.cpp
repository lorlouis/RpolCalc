#include <string>
#include <stdexcept>
#include "generic.h"

bool generic::isNumber(char* s)
{
    std::string str(s);
    try
    {
        std::stod(str);
    }
    catch(std::invalid_argument e)
    {
        return false;
    }
    catch(std::out_of_range e)
    {
        return false;
    }
    return true;
}
int generic::toNumber(char* s)
{
    std::string str(s);
    if(generic::isNumber(s))
    {
        return (int)std::stoi(str);
    } 
    else
    {
        throw "invalid argument";
    }
}
