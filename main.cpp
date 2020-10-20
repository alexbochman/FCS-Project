
#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>
#include <optional>

#include "Alphabet.hpp"
#include "DFA.hpp"

using namespace std;

template <typename T>
void test_trace(DFA<T> m, int count) {
    cout << "\nPOSSIBLE STRING : ";
    auto output = possibleString(m);

    if (output.has_value())
        output->printString();
    else
        cout << "[NO POSSIBLE STRING]";

    cout << "\nINPUT\t       ACCEPT STATUS\tTRACE\n\n";
    Alphabet E = m.getAlpha();
    for (int i = 0; i < count; i++) {
        cout << "Lexi(" << i << "): ";
        isStrAccepted_trace(m, E.lexi(i));
    }
    cout << "--------------------------------------------------\n\n";
}

template <typename T>
void test_noTrace(DFA<T> m, int count) {
    cout << "\nPOSSIBLE STRING : ";
    auto output = possibleString(m);
    if (output.has_value())
        output->printString();
    else
        cout << "[NO POSSIBLE STRING]";

    cout << "\nINPUT\t       ACCEPT STATUS\tTRACE\n\n";
    Alphabet E = m.getAlpha();
    for (int i = 0; i < count; i++) {
        cout << "Lexi(" << i << "): ";
        isStrAccepted_noTrace(m, E.lexi(i));
    }
    cout << "--------------------------------------------------\n\n";
}

// Task 7 - Write a function that returns a DFA that only accepts the given Character
DFA<int> givenCharacterDFA(string input) {
    Alphabet E;
    E.insert(input);
    DFA<int> m([](int qi) { return qi == 0 || qi == 1 || qi == 2; }, E, 0,
            [input](int qi, Character c) {
                switch (qi) {
                case 0: return c.getCharacterValue() == input ? 1 : 2;
                case 1: return 2;
                case 2: return 2;
                default: return 2; } },
            [](int qi) { return qi == 1; });
    return m;
}

// Task 10 - Write a function that given a DFA and a string, determines if the string is accepted.
template <typename T>
bool isStrAccepted_trace(DFA<T> m, Str w) {
    bool accepted = m.accepts(w);
    w.printString();
    if (accepted) cout << "\tAccepted\t";
    else cout << "\tRejected\t";
    m.trace();
    return accepted;
}

template <typename T>
bool isStrAccepted_noTrace(DFA<T> m, Str w) {
    bool accepted = m.accepts(w);
    w.printString();
    if (accepted)
        cout << "\tAccepted\t";
    else
        cout << "\tRejected\t";
    cout << endl;
    return accepted;
}

// Task 12 - Write a function that given a DFA, returns a string that would be accepted (or false if this is not possible).
template <typename T>
Str searchAlgo(DFA<T> m, T qi, std::vector<T> *visited, Str output) {
    vector<Character> E = m.getAlpha().getAlphabetVector();
    if (m.getAcceptingStates()(qi))
        return output;

    for (int i = 0; i < (int)E.size(); i++) {
        auto qNext = m.getTransitions()(qi, E.at(i));
        auto it = std::find(visited->begin(), visited->end(), qNext);
        if (it == visited->end()) {
            visited->push_back(qNext);
            output.pushBack(E.at(i));
            output = searchAlgo(m, qNext, visited, output);
            if(output.getSize() > 0)
                return output;
        }
    }
    return output;
}

template <typename T>
std::optional<Str> possibleString(DFA<T> m) {
    std::vector<T> visited{m.getStartState()};
    Str output;
    output = searchAlgo(m, m.getStartState(), &visited, output);

    if (m.accepts(output))
        return output;
    return std::nullopt;
}

// Task 13 - (Complement) Write a function that takes one DFA and returns a DFA that accepts what the given one doesn't (and vice versa).
template <typename T>
DFA<T> complementDFA(DFA<T> m) {
    auto F = m.getAcceptingStates();
    function<bool(T)> fPrime = [=](int qi) { return !F(qi); };
    return DFA<T>(m.getStates(), m.getAlpha(), m.getStartState(), m.getTransitions(), fPrime);
}

// Task 14 - (Union) Write a function that takes two DFAs and returns a third DFA that accepts a string that either DFA accepts.
template <typename F, typename G>
DFA<std::pair<F, G>> unionDFAs(DFA<F> m1, DFA<G> m2) {
    std::function<bool(F)> Q1 = m1.getStates();
    std::function<bool(G)> Q2 = m2.getStates();
    std::function<F(F, Character)> D1 = m1.getTransitions();
    std::function<G(G, Character)> D2 = m2.getTransitions();
    std::function<bool(F)> A1 = m1.getAcceptingStates();
    std::function<bool(G)> A2 = m2.getAcceptingStates();

    return DFA<std::pair<F, G>> ([Q1, Q2](std::pair<F, G> state) { return Q1(state.first) && Q2(state.second); },
                                m1.getAlpha(), std::pair<F, G>{m1.getStartState(), m2.getStartState()},
                                [D1, D2](std::pair<F, G> state, Character c) {
                                    F q1 = D1(state.first, c);
                                    G q2 = D2(state.second, c);
                                    return std::pair<F, G>{q1, q2};
                                },
                                [A1, A2](std::pair<F, G> state) { return A1(state.first) || A2(state.second); });
}

// Task 16 - (Intersect) Write a function that takes two DFAs and returns a third DFA that accepts a string if both arguments accepts it.
template <typename F, typename G>
DFA<std::pair<F, G>> intersectDFAs(DFA<F> m1, DFA<G> m2) {
    std::function<bool(F)> Q1 = m1.getStates();
    std::function<bool(G)> Q2 = m2.getStates();
    std::function<F(F, Character)> D1 = m1.getTransitions();
    std::function<G(G, Character)> D2 = m2.getTransitions();
    std::function<bool(F)> A1 = m1.getAcceptingStates();
    std::function<bool(G)> A2 = m2.getAcceptingStates();

    return DFA<std::pair<F, G>>([Q1, Q2](std::pair<F, G> state) { return Q1(state.first) && Q2(state.second); },
                                m1.getAlpha(), std::pair<F, G>{m1.getStartState(), m2.getStartState()},
                                [D1, D2](std::pair<F, G> state, Character c) {
                                    F q1 = D1(state.first, c);
                                    G q2 = D2(state.second, c);
                                    return std::pair<F, G>{q1, q2};
                                },
                                [A1, A2](std::pair<F, G> state) { return A1(state.first) && A2(state.second); });
}

// Task 18 - (Subset) Write a function which takes two DFAs (X and Y) and returns whether every string accepted by X is also accepted by Y.
template <typename T1, typename T2>
bool subset(DFA<T1> X, DFA<T2> Y) { return !possibleString(intersectDFAs(complementDFA(Y), X)).has_value(); }

// Task 20 - (Equality) Write a function which takes two DFAs (X and Y) and returns whether every string accepted by X is also accepted by Y and vice versa.
template <typename T1, typename T2>
bool isEqual(DFA<T1> X, DFA<T2> Y) { return subset(X, Y) && subset(Y, X); }

void runDfaTestCases() {

    Alphabet binaryAlpha;
    binaryAlpha.setAlphaVector(vector<Character>{Character("0"), Character("1")});
    Alphabet abAlpha;
    abAlpha.setAlphaVector(vector<Character>{Character("a"), Character("b")});
    Alphabet alexAlpha;
    alexAlpha.setAlphaVector(vector<Character>{Character("A"), Character("L"), Character("E"), Character("X")});

    { // DFAs Initialized Below, Test Calls At The Bottom

        // [1] ACCEPTS NO STRINGS
        DFA<int> noString([](int qi) { return qi == 0; }, binaryAlpha, 0,
                            [](int qi, Character c) { return 0; },
                            [](int qi) { return 0; });

        // [2] ACCEPT ONLY EMPTY STRING
        DFA<int> emptyString([](int qi) { return qi == 0 || qi == 1; }, binaryAlpha, 0,
                                [](int qi, Character c) { return 1; },
                                [](int qi) { return qi == 0; });

        // [3] FUNCTION RETURNS A DFA THAT ONLY ACCEPTS GIVEN CHARACTER (TASK 7)
        DFA<int> task7DFA = givenCharacterDFA("X");

        // [4] STRINGS OF EVEN LENGTH
        DFA<int> evenLength([](int qi) { return qi == 0 || qi == 1; }, binaryAlpha, 0,
                            [](int qi, Character c) { return !qi; },
                            [](int qi) { return !qi; });

        // [5] STRINGS OF EVEN BINARY NUMBERS
        DFA<int> evenBinary([](int qi) { return qi == 0 || qi == 1; }, binaryAlpha, 0,
                            [](int qi, Character c) { return !(c.getCharacterValue() == "0"); },
                            [](int qi) { return qi == 0; });

        // [6] BOOK FIGURE 1.12
        DFA<int> bookFigure112([](int qi) { return qi == 0 || qi == 1 || qi == 2 || qi == 3 || qi == 4; }, abAlpha, 0,
                            [](int qi, Character c) {
                switch (qi) {
                case 0: return c.getCharacterValue() == "a" ? 1 : 2;
                case 1: return c.getCharacterValue() == "a" ? 1 : 3;
                case 2: return c.getCharacterValue() == "a" ? 4 : 2;
                case 3: return c.getCharacterValue() == "a" ? 1 : 3;
                case 4: return c.getCharacterValue() == "a" ? 4 : 2;
                default: return 0; } },
                            [](int qi) { return qi == 1 || qi == 2; });

        // [7] ONLY ACCEPT IF STRING ENDS IN A 1
        DFA<int> endsIn1([](int qi) { return qi == 0 || qi == 1; }, binaryAlpha, 0,
                            [](int qi, Character c) { return c.getCharacterValue() == "1"; },
                            [](int qi) { return qi == 1; });

        // [8] ONLY ACCEPT IF STRING CONTAINS AN ODD NUMBER OF 1s (BOOK FIGURE 1.20)
        DFA<int> bookFigure120([](int qi) { return qi == 0 || qi == 1; }, binaryAlpha, 0,
                            [](int qi, Character c) {
                switch (qi) {
                case 0: return c.getCharacterValue() == "1";
                case 1: return c.getCharacterValue() == "0";
                default: return false; } },
                            [](int qi) { return qi == 1; });

        // [9] ONLY ACCEPT IF ALEX IS A SUBSTRING
        DFA<int> alexDfa([](int qi) { return qi == 0 || qi == 1 || qi == 2 || qi == 3 || qi == 4; }, alexAlpha, 0,
                            [](int qi, Character c) {
                switch (qi) {
                case 0: return c.getCharacterValue() == "A" ? 1 : 0;
                case 1:
                    if(c.getCharacterValue() == "A") return 1;
                    if(c.getCharacterValue() == "L") return 2;
                    else return 0;
                case 2: return c.getCharacterValue() == "E" ? 3 : 0;
                case 3: return c.getCharacterValue() == "X" ? 4 : 0;
                case 4: return 4;
                default: return 0; } },
                            [](int qi) { return qi == 4; });

        cout << "====================================================================";
        cout << "\n[1] ACCEPTS NO STRINGS\n";
        cout << "====================================================================\n\n";
        test_trace(noString, 12);
        test_trace(complementDFA(noString), 12);

        cout << "====================================================================";
        cout << "\n[2] ACCEPT ONLY EMPTY STRING\n";
        cout << "====================================================================\n\n";
        test_trace(emptyString, 12);
        test_trace(complementDFA(emptyString), 12);
        test_noTrace(unionDFAs(emptyString, noString), 12);

        cout << "====================================================================";
        cout << "\n[3] FUNCTION RETURNS A DFA THAT ONLY ACCEPTS GIVEN CHARACTER (TASK 7)\n";
        cout << "====================================================================\n\n";
        test_trace(task7DFA, 5);
        test_trace(complementDFA(task7DFA), 5);

        cout << "====================================================================";
        cout << "\n[4] STRINGS OF EVEN LENGTH\n";
        cout << "====================================================================\n\n";
        test_trace(evenLength, 12);
        test_trace(complementDFA(evenLength), 12);
        test_noTrace(unionDFAs(complementDFA(evenLength), emptyString), 12);
        test_noTrace(intersectDFAs(evenLength, emptyString), 12);

        cout << "====================================================================";
        cout << "\n[5] STRINGS OF EVEN BINARY NUMBERS\n";
        cout << "====================================================================\n\n";
        test_trace(evenBinary, 12);
        test_trace(complementDFA(evenBinary), 12);
        test_noTrace(unionDFAs(evenLength, evenBinary), 12);
        test_noTrace(intersectDFAs(evenLength, evenBinary), 12);
        test_noTrace(intersectDFAs(evenLength, evenBinary), 12);
        test_noTrace(intersectDFAs(complementDFA(evenLength), evenBinary), 12);
        test_noTrace(intersectDFAs(evenLength, complementDFA(evenBinary)), 12);

        cout << "====================================================================";
        cout << "\n[6] BOOK FIGURE 1.12\n";
        cout << "====================================================================\n\n";
        test_trace(bookFigure112, 12);
        test_trace(complementDFA(bookFigure112), 12);

        cout << "====================================================================";
        cout << "\n[7] ONLY ACCEPT IF STRING ENDS IN A 1\n";
        cout << "====================================================================\n\n";
        test_trace(endsIn1, 12);
        test_trace(complementDFA(endsIn1), 12);
        test_noTrace(unionDFAs(endsIn1, evenBinary), 12);
        test_noTrace(unionDFAs(endsIn1, evenLength), 12);
        test_noTrace(intersectDFAs(endsIn1, evenLength), 12);
        test_noTrace(intersectDFAs(endsIn1, evenLength), 12);

        cout << "====================================================================";
        cout << "\n[8] ONLY ACCEPT IF STRING CONTAINS AN ODD NUMBER OF 1s (BOOK FIGURE 1.20)\n";
        cout << "====================================================================\n\n";
        test_trace(bookFigure120, 12);
        test_trace(complementDFA(bookFigure120), 12);

        cout << "====================================================================";
        cout << "\n[9] ONLY ACCEPT IF ALEX IS A SUBSTRING\n";
        cout << "====================================================================\n\n";
        test_trace(alexDfa, 12);
        test_trace(complementDFA(alexDfa), 12);

        cout << "====================================================================";
        cout << "\nTASK 18 & 19 - SUBSET TESTS\n";
        cout << "====================================================================\n";
        cout << "\nsubset(endsIn1, evenLength)\t\t  :\t" << subset(endsIn1, evenLength);
        cout << "\nsubset(evenLength, endsIn1)\t\t  :\t" << subset(evenLength, endsIn1);
        cout << "\nsusbset(evenBinary, emptyString)\t  :\t" << subset(evenBinary, emptyString);
        cout << "\nsusbset(evenLength, emptyString)\t  :\t" << subset(evenLength, emptyString);
        cout << endl;
        cout << "\nsusbset(emptyString, evenBinary)\t  :\t" << subset(emptyString, evenBinary);
        cout << "\nsusbset(emptyString, evenLength)\t  :\t" << subset(emptyString, evenLength);
        cout << "\nsusbset(noString, emptyString)\t\t  :\t" << subset(noString, emptyString);
        cout << "\nsusbset(emptyString, noString)\t\t  :\t" << subset(noString, emptyString);
        cout << "\nsusbset(alexDfa, complementDFA(noString)) :\t" << subset(alexDfa, complementDFA(noString));

        cout << "\n\n====================================================================";
        cout << "\nTASK 20 & 21 - EQUALITY TESTS\n";
        cout << "====================================================================\n";
        cout << "\nisEqual(endsIn1, evenLength)\t\t  :\t" << isEqual(endsIn1, evenLength);
        cout << "\nisEqual(bookFigure120, bookFigure112)\t  :\t" << isEqual(bookFigure120, bookFigure112);
        cout << "\nisEqual(noString, emptyString)\t\t  :\t" << isEqual(noString, emptyString);
        cout << "\nisEqual(noString, evenLength)\t\t  :\t" << isEqual(noString, evenLength);
        cout << endl;
        cout << "\nisEqual(endsIn1, endsIn1)\t\t  :\t" << isEqual(endsIn1, endsIn1);
        cout << "\nisEqual(noString, noString)\t\t  :\t" << isEqual(noString, noString);
        cout << "\nisEqual(emptyString, emptyString)\t  :\t" << isEqual(emptyString, emptyString);
        cout << "\nisEqual(alexDfa, alexDfa)\t\t  :\t" << isEqual(alexDfa, alexDfa);
        cout << endl;
    }
}


int main() {
    runDfaTestCases();
    cout << endl;
}
