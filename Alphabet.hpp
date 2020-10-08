
#ifndef ALPHABET_H
#define ALPHABET_H

#include <string.h>
#include <iostream>
#include <vector>

class Character {
public:
    Character() {characterValue = "[DEFAULT CHARACTER CONSTRUCTOR]";}
    Character(std::string string) { this->characterValue = string; }
    ~Character() {}
    std::string getCharacterValue() { return characterValue; }
private:
    std::string characterValue;
};

class Str {
private:
    std::vector<Character> strVector;
public:
    Str(){}
    Str(std::vector<Character> cVect) : strVector(cVect) {}
    ~Str() {}
    void insert(Character c) { strVector.insert(strVector.begin(), c); }
    std::vector<Character> getStr() { return strVector; }
    void printString() {
        if (strVector.empty())
            std::cout << "\u03B5";
        else
            for (Character c : strVector)
                std::cout << c.getCharacterValue();
    }
};

class Alphabet {
private:
    std::vector<Character> alphabetVector;
public:
    Alphabet();
    ~Alphabet();
    void insert(Character);
    void setAlphaVector(std::vector<Character> a) {this->alphabetVector = a;}
    std::vector<Character> getAlphabetVector();
    Str lexi(int n);
};

#endif
