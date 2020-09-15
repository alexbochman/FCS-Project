
#include <iostream>
#include <math.h>
#include "Alphabet.hpp"

Alphabet::Alphabet() {}
Alphabet::~Alphabet() {}

void Alphabet::printVector(std::vector<Character> vect)
{
    std::cout << "\nPrint vector output: " << std::endl;

    if(vect.empty())
        std::cout << "Alphabet vector is empty." << std::endl;
    else
        for(Character c : vect)
            std::cout << "Vector: c.getCharacterValue(): " << c.getCharacterValue() << std::endl;
}

void Alphabet::insert(Character c) { alphabetVector.push_back(c); }

std::vector<Character> Alphabet::getAlphabetVector() {return alphabetVector;}

Str Alphabet::lexi(int input)
{
    Str str;
    int amountOfCharacter = alphabetVector.size();
    if(input == 0) return str;
    int exp = 0;
    while(1)
    {
        if(pow(amountOfCharacter, exp) <= input)
        {
            input -= pow(amountOfCharacter, exp);
            exp++;
        }
        else
        {
            for(int j = 0; j < exp; j++)
            {
                str.insert(alphabetVector.at(input % amountOfCharacter));
                input = input / alphabetVector.size();
            }
            return str;
        }
    }
}