
#ifndef STR_H
#define STR_H

#include "Character.hpp"
#include <vector>

class Str
{
private:
    std::vector<Character> strVector;
public:
    Str();
    ~Str();
    void printString();
    void fillString(Character c);
    std::vector<Character> getString();
};



#endif