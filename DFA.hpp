#ifndef DFA_HPP
#define DFA_HPP

#include "Alphabet.hpp"
#include <iostream>
#include <vector>

class State
{
private:

public:
    State(){};
    ~State() {}
};

class DFA
{
private:
    Character startState;
    std::vector<Character> states;
    std::vector<Character> acceptingStates;
    State myState();

public:
    DFA();
    ~DFA();
};



#endif