
#ifndef ALPHABET_H
#define ALPHABET_H

#include <string.h>

#include <iostream>
#include <vector>

class Character {
   public:
    Character() { characterValue = "\u03B5"; }
    Character(std::string string) { this->characterValue = string; }
    Character(char c) { this->characterValue = c; }
    ~Character() {}
    std::string getCharacterValue() {
        if (characterValue.empty())
            characterValue = "\u03B5";
        return characterValue;
    }

   private:
    std::string characterValue;
};

class Str {
   private:
    std::vector<Character> strVector;
    bool failed = false;
    std::string s;

   public:
    Str() {}
    Str(std::vector<Character> cVect) : strVector(cVect) {}
    Str(std::string s) : s(s) {
        for (unsigned int i = 0; i < this->s.size(); i++)
            strVector.push_back(Character(this->s.substr(i, 1)));
    }
    ~Str() {}

    void eraseFront() { strVector.erase(strVector.begin()); }
    void insert(Character c) { strVector.insert(strVector.begin(), c); }
    std::vector<Character> getStr() { return strVector; }
    void setFail() { failed = true; }
    bool hasFailed() { return failed; }
    void pushBack(Character c) { strVector.push_back(c); }
    int getSize() { return strVector.size(); }
    bool isEmpty() { return strVector.empty(); }
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
    void setAlphaVector(std::vector<Character> a) { this->alphabetVector = a; }
    std::vector<Character> getAlphabetVector();
    Str lexi(int n);
};

#endif
