
#ifndef NFA_HPP
#define NFA_HPP

#include <functional>
#include <optional>
#include <utility>
#include <iostream>
#include <tuple>
#include <vector>

#include "Alphabet.hpp"
#include "DFA.hpp"

// Task 23 - Define NFAs
template <class T>
class NFA {
   public:
    std::function<bool(T)> Q;
    T q0;
    std::function<std::vector<T>(T, Character)> d;
    std::function<bool(T)> F;
    std::vector<T> visitedStates;

    NFA(std::function<bool(T)> Q, T q0,
        std::function<std::vector<T>(T, Character)> d,
        std::function<bool(T)> F)
        : Q(Q), q0(q0), d(d), F(F){};

    ~NFA(){};
};

// Task 28 - Define Trace Tree
template <class T>
class TraceTree {
   public:
    T qi;
    bool accepted;
    Character c;
    std::vector<TraceTree<T>> branches;

    TraceTree() {}

    TraceTree(T qi, bool accepted, Character c, std::vector<TraceTree<T>> branches)
        : qi(qi), accepted(accepted), c(c), branches(branches) {}

    TraceTree(T qi, bool accepted, Character c)
        : qi(qi), accepted(accepted), c(c) {}

    // Task 30 - (Forking) Write a function that given an NFA and a string, returns a tree of all possible traces.
    TraceTree explore(NFA<T> nfa, Str str) { return exploreHelper(nfa, str, nfa.q0); }

    TraceTree exploreHelper(NFA<T> nfa, Str str, T qi) {
        std::vector<TraceTree<T>> branches;
        std::vector<T> epsilonVect = nfa.d(qi, Character("\u03B5"));

        // First get all of the possible epsilon transitions
        for (unsigned int i = 0; i < epsilonVect.size(); i++)
            branches.push_back(exploreHelper(nfa, str, epsilonVect.at(i)));

        // then if the input string isn't empty, get all of the character transitions.
        if (str.getSize() > 0) {
            Character c(str.getStr().at(0));
            str.eraseFront();
            std::vector<T> transitionVector = nfa.d(qi, c);

            // get all of the possible character transitions
            for (int i = 0; i < (int)transitionVector.size(); i++)
                branches.push_back(exploreHelper(nfa, str, transitionVector.at(i)));

            // return trace tree with both epsilon and character transitions
            return TraceTree<T>(qi, nfa.F(qi), c, branches);
        }
        // otherwise, return trace tree with just epsilon transitions
        return TraceTree<T>(qi, nfa.F(qi), c, branches);
    }

    void printTree(TraceTree tt, int count) {
        std::cout << "\n";

        for (int i = 0; i < count; i++)
            std::cout << "\t";
        count++;

        std::cout << "[ State: q" << tt.qi << ", NextChar: " << tt.c.getCharacterValue();

        for (auto i : tt.branches)
            printTree(i, count);

        std::cout << std::endl;
        for (int i = 1; i < count; i++)
            std::cout << "\t";

        std::cout << "]";
    }

};

#endif