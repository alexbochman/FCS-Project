#include "DFA.hpp"

Character DFA::getTransValue(int currentState, int targetState) {
    Character c;
    for(auto i : E.getAlphabetVector()) {
        if(d(currentState, i) == targetState)
            return i;
    }
    return c;
}

bool DFA::accepts(Str w) {
    int qi = q0;
    visitedStates.push_back(qi);
    for (Character c : w.getStr()) {
        qi = d(qi, c);
        visitedStates.push_back(qi);
    }
    return F(qi);
}

// Task 11
void DFA::trace() {
    std::cout << "\u03B5";
    for (auto i : visitedStates)
        std::cout << " -> " << i;
    std::cout << '\n';
}
