#ifndef DFA_HPP
#define DFA_HPP

#include "Alphabet.hpp"
#include <functional>
#include <iostream>
#include <vector>
#include <tuple>

class DFA
{
private:
    std::function<bool(int)> Q;
    Alphabet E;
    int q0;
    std::function<int(int, Character)> d;
    std::function<bool(int)> F;
    std::vector<int> visitedStates;

public:
    DFA(std::function<bool(int)> Q, Alphabet E, int q0,
        std::function<int(int, Character)> d,
        std::function<bool(int)> F)
        : Q(Q), E(E), q0(q0), d(d), F(F){};

    void trace();
    bool accepts(Str w);
    int getStartState() { return q0; }
    Character getTransValue(int currentState, int targetState);
    std::function<bool(int)> getStates() { return Q; }
    std::function<bool(int)> getAcceptingStates() { return F; }
    std::function<int(int, Character)> getTransitions() { return d; }
    Alphabet getAlpha() { return E; }

};

#endif