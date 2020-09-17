
#include <iostream>
#include <math.h>
#include "Alphabet.hpp"

Alphabet::Alphabet() {}
Alphabet::~Alphabet() {}
void Alphabet::insert(Character c) { alphabetVector.push_back(c); }
std::vector<Character> Alphabet::getAlphabetVector() { return alphabetVector; }

void Alphabet::printVector()
{
    std::cout << "\nPrint vector output: " << std::endl;

    if(alphabetVector.empty())
        std::cout << "Alphabet vector is empty." << std::endl;
    else
        for(Character c : alphabetVector)
            std::cout << "Vector: c.getCharacterValue(): " << c.getCharacterValue() << std::endl;
}

Str Alphabet::lexi(int input)
{
    Str str;
    int amountOfCharacters = alphabetVector.size();
    if(input == 0) return str;
    int exp = 0;
    while(1)
    {
        if(pow(amountOfCharacters, exp) <= input)
        {
            input -= pow(amountOfCharacters, exp);
            exp++;
        }
        else
        {
            for(int j = 0; j < exp; j++)
            {
                str.insert(alphabetVector.at(input % amountOfCharacters));
                input = input / alphabetVector.size();
            }
            return str;
        }
    }
}