
#ifndef NFA_HPP
#define NFA_HPP

#include "Alphabet.hpp"
#include "DFA.hpp"
#include <functional>
#include <iostream>
#include <vector>
#include <tuple>

template <class T>
class NFA {
public:
    std::function<bool(T)> Q;
    Alphabet E;
    T q0;
    std::function<std::vector<T>(T, Character)> d;
    std::function<bool(T)> F;
    std::vector<T> visitedStates;

    NFA(std::function<bool(T)> Q, Alphabet E, T q0,
        std::function<std::vector<T>(T, Character)> d,
        std::function<bool(T)> F)
        : Q(Q), E(E), q0(q0), d(d), F(F){};

    ~NFA() {};

};

#endif