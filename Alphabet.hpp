
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
    Character() {characterValue = "[DEFAULT CHARACTER CONSTRUCTOR]";}
    Character(std::string string) { this->characterValue = string; }
    ~Character() {}
    void setCharacterValue(std::string string) { this->characterValue = string; }
    std::string getCharacterValue() { return characterValue; }

private:
    std::string characterValue;
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
    bool isEmpty() { return strVector.empty(); }
    void insert(Character c) { strVector.insert(strVector.begin(), c); }
    std::vector<Character> getStr() { return strVector; }
    std::string popFront()
    {
        std::string temp = strVector.front().getCharacterValue();
        strVector.erase(strVector.begin());
        return temp;
    }
    void printString()
    {
        if (strVector.empty())
            std::cout << "\u03B5";
        else
            for (Character c : strVector)
                std::cout << c.getCharacterValue();
    }

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
    void insert(Character);
    std::vector<Character> getAlphabetVector();
    Str lexi(int n);

};

#endif
