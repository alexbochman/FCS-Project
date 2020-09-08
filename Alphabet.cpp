
#include <iostream>
#include <math.h>
#include "Alphabet.hpp"

Alphabet::Alphabet()
{
    alphabetVector.push_back(Character("0"));
    alphabetVector.push_back(Character("1"));
    alphabetVector.push_back(Character("2"));
    alphabetVector.push_back(Character("3"));
    alphabetVector.push_back(Character("4"));
    alphabetVector.push_back(Character("5"));
    alphabetVector.push_back(Character("6"));
    alphabetVector.push_back(Character("7"));
    alphabetVector.push_back(Character("8"));
    alphabetVector.push_back(Character("9"));

    alphabetVector.push_back(Character("A"));
    alphabetVector.push_back(Character("B"));
    alphabetVector.push_back(Character("C"));
    alphabetVector.push_back(Character("D"));
    alphabetVector.push_back(Character("E"));
    alphabetVector.push_back(Character("F"));
}

Alphabet::~Alphabet() {}

void Alphabet::printVector(std::vector<Character> vect)
{
    std::cout << "\nPrint vector output: " << std::endl;

    if(vect.empty())
        std::cout << "Alphabet vector is empty." << std::endl;
    else
        for(Character c : vect)
            std::cout << "Vector: c.get_sValue(): " << c.get_sValue() << std::endl;
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
                str.insert(alphabetVector.at(input % amount_of_characters));
                input = input / alphabetVector.size();
            }
            return str;
        }
    }
}