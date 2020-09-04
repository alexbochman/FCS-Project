
#include <iostream>
#include "Str.hpp"

Str::Str()
{
}

Str::~Str()
{
}

void Str::printString()
{
    if (strVector.empty())
        std::cout << "{}";
    else
        for (Character c : strVector)
            std::cout << c.get_nValue();
}

void Str::fillString(Character c) { strVector.insert(strVector.begin(), c); }

std::vector<Character> Str::getString() { return strVector; }