
#ifndef ALPHABET_H
#define ALPHABET_H

#include <iostream>
#include <vector>

// Helper class Character
// Defined by integer data type
class Character
{
public:
    Character() {}
    Character(int n) { this->nValue = n; }
    ~Character() {}
    void set_nValue(int n) { this->nValue = n; }
    int get_nValue() { return nValue; }

private:
    int nValue;
};

// Helper class Str
// Defined by a vector of Characters (class object)
// Functions allow for:
// -- inserting into vector<Character> strVector
// -- printing contents of vector<Character> strVector
// -- get vector<Character> strVector
class Str
{
private:
    std::vector<Character> strVector;

public:
    Str(){}
    ~Str() {}
    void printString()
    {
        if (strVector.empty())
            std::cout << "\u03B5";
        else
            for (Character c : strVector)
                std::cout << c.get_nValue();
    }
    void insert(Character c) { strVector.insert(strVector.begin(), c); }
    std::vector<Character> getString() { return strVector; }
};

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
