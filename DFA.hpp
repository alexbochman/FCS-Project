#ifndef DFA_HPP
#define DFA_HPP

#include "Alphabet.hpp"
#include <iostream>
#include <vector>
#include <tuple>

// Minor class State:
// - States are the nodes in a DFA
// - Each state has its own value, which is a stateID
// - Each state has a tuple that knows the value when making a transition to another state
// - Each state has an acceptStatus bool that can be checked to see if the DFA can end on that state
class State
{
private:
    bool acceptStatus;
    int stateID;
    std::vector<std::tuple<int, Character>> transitions; // int: transition destination, Character: transition value

public:
    State();
    State(bool acceptStatus, int stateID);
    ~State();

    bool getAcceptStatus() { return this->acceptStatus; }
    int getStateID() { return stateID; }
    void insertTransition(int stateID, Character transitionValue);
    std::vector<std::tuple<int, Character>> getTransitionsVector() { return transitions; }

    int getIDfromTuple(int location) { return std::get<0>(transitions.at(location)); }
    std::string getTransValueFromTuple(int location) { return std::get<1>(transitions.at(location)).getCharacterValue();}
};

// Major class DFA:
// - statesVector is a vector that contains all of the States
// - currentState tracks the current state/position in the dfaVector
// - startState is the state
class DFA
{
private:
    State currentState;
    State startState;
    std::vector<State> statesVector;
    Alphabet alphabet;
    Str input;

public:
    DFA(Alphabet alphabet, Str input);
    ~DFA();
    void insertStatesVector(State state) {statesVector.push_back(state);}
    void generateDFA(int testNumber);
    void runDFA();
    bool isAccepted();
};



#endif