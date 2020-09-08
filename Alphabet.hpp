
#ifndef ALPHABET_H
#define ALPHABET_H

#include <string.h>
#include <iostream>
#include <vector>

// Minor class Character:
// - Defined by integer data type
class Character
{
public:
    Character() {sValue = "-1";}
    Character(std::string string) { this->sValue = string; }
    ~Character() {}
    void set_sValue(std::string string) { this->sValue = string; }
    std::string get_sValue() { return sValue; }

private:
    std::string sValue;
};

// Minor class Str:
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
                std::cout << c.get_sValue();
    }
    void insert(Character c) { strVector.insert(strVector.begin(), c); }
    std::vector<Character> getString() { return strVector; }
};

// Major class Alphabet:
// - print vector displays contents of the Alphabet
// - Given a number n, Lexi returns the nth Str in an Alphabet's lexicographic ordering
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
