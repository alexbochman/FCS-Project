#ifndef DFA_HPP
#define DFA_HPP

#include "Alphabet.hpp"
#include <functional>
#include <iostream>
#include <vector>
#include <tuple>

template <class T>
class DFA {
public:
    std::function<bool(T)> Q;
    Alphabet E;
    T q0;
    std::function<T(T, Character)> d;
    std::function<bool(T)> F;
    std::vector<T> visitedStates;

    DFA(std::function<bool(T)> Q, Alphabet E, T q0,
        std::function<T(T, Character)> d,
        std::function<bool(T)> F)
        : Q(Q), E(E), q0(q0), d(d), F(F){};

    void trace() {
    std::cout << "\u03B5";
    for (auto i : visitedStates)
        std::cout << " -> " << std::to_string(i);
    std::cout << '\n';
    }

    bool accepts(Str w) {
        T qi = q0;
        visitedStates.push_back(qi);
        for (Character c : w.getStr()) {
            qi = d(qi, c);
            visitedStates.push_back(qi);
        }
        return F(qi);
    }

    T getStartState() { return q0; }

    Character getTransValue(T currentState, T targetState) {
        Character c;
        for (auto i : E.getAlphabetVector()) {
            if (d(currentState, i) == targetState)
                return i;
        }
        return c;
    }

    std::function<bool(T)> getStates() { return Q; }

    std::function<bool(T)> getAcceptingStates() { return F; }

    std::function<T(T, Character)> getTransitions() { return d; }

    Alphabet getAlpha() { return E; }

    DFA unionDFAs(DFA m);

};

#endif