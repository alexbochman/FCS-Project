#ifndef DFA_HPP
#define DFA_HPP

#include "Alphabet.hpp"
#include <iostream>
#include <vector>

// Minor class State:
// - States are the nodes in a DFA
// - Each state has its own value, which is a Character value
// - Each state knows of each of its outward connections to other states
class State
{
private:
    Character stateValue;
    std::vector<Character> outwardConnections;

public:
    State() {stateValue.set_sValue("-1");}
    State(Character stateValue) {this->stateValue = stateValue;}
    ~State() {}

    std::string getStateValue() {return stateValue.get_sValue();}
};

// Major class DFA:
// - startState is beginning of a DFA
// - dfaVector is a vector that contains ALL of the States
// - acceptingStates is a vector that contains all of the accepting States, if any
class DFA
{
private:
    State startState;
    std::vector<State> dfaVector;
    std::vector<State> acceptingStates;

public:
    DFA();
    ~DFA();
};



#endif