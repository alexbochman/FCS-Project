
#ifndef ALPHABET_H
#define ALPHABET_H

#include "Character.hpp"
#include "Str.hpp"

class Alphabet
{
private:
    std::vector<Character> alphabetVector;

public:
    Alphabet();
    ~Alphabet();
    void printVector(std::vector<Character> vect);
    Str lexi(int n);
};

#endif