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
    State() {}
    State(bool acceptStatus, int stateID) : acceptStatus(acceptStatus), stateID(stateID) {}
    ~State() {};
    int getStateID() { return stateID; }
    bool getAcceptStatus() { return this->acceptStatus; }
    int getIDfromTuple(int location) { return std::get<0>(transitions.at(location)); }
    std::vector<std::tuple<int, Character>> getTransitionsVector() { return transitions; }
    std::string getTransValueFromTuple(int location) { return std::get<1>(transitions.at(location)).getCharacterValue(); }

    Character getTransValueGivenID(int id)
    {
        Character c;
        for(std::tuple<int, Character> i : transitions)
        {
            //std::cout << "\n1. NUH";
            if(std::get<0>(i) == id)
                return std::get<1>(i);
        }
        return c;
    }

    void insertTransition(int stateID, Character transitionValue)
    {
        // Function creates a tuple with the state and its transition value and
        // inserts the tuple into a vector. As in: GO TO [stateID] WITH VALUE OF [transitionValue]
        std::tuple<int, Character> transition;
        transition = std::make_tuple(stateID, transitionValue);
        transitions.push_back(transition);
    }
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
    std::vector<int> traceVector;
    Alphabet alphabet;
    Str input;

public:
    DFA();
    DFA(Str input);
    DFA(Alphabet a);
    DFA(Alphabet alphabet, Str input);
    ~DFA();
    void initDFA(int testNumber);
    void setCurrentState(State s);
    void setStartState(State s);
    void setInput(Str input);
    void setAlphabet(Alphabet alphabet);
    void runDFA();
    void printTrace();
    bool hasAnAcceptState();
    std::vector<int> getTrace(Str input);
    std::vector<State> getStatesVector();
    State getCurrentState();
    Str getInput();
    DFA task7(Character c);
};



#endif