
#include <iostream>
#include <math.h>
#include "Alphabet.hpp"

Alphabet::Alphabet()
{
    alphabetVector.push_back(Character(0));
    alphabetVector.push_back(Character(1));
}

Alphabet::~Alphabet() {}

void Alphabet::printVector(std::vector<Character> vect)
{
    std::cout << "\nPrint vector output: " << std::endl;

    if(vect.empty())
        std::cout << "This vector is empty." << std::endl;
    else
        for(Character c : vect)
            std::cout << "Vector: c.get_nValue(): " << c.get_nValue() << std::endl;
}

Str Alphabet::lexi(int input)
{
    Str str;
    int amount_of_characters = alphabetVector.size();
    if(input == 0) return str;
    int exp = 0;
    while(1)
    {
        if(pow(amount_of_characters, exp) <= input)
        {
            input -= pow(amount_of_characters, exp);
            exp++;
        }
        else
        {
            for(int j = 0; j < exp; j++)
            {
                str.fillString(alphabetVector.at(input % amount_of_characters));
                input = input / alphabetVector.size();
            }
            return str;
        }
    }
}