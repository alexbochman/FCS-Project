
#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <utility>
#include <cmath>

#include "Alphabet.hpp"
#include "DFA.hpp"
#include "NFA.hpp"
#include "Regex.hpp"

using namespace std;

auto popFront(string &s) {
    string temp = s.substr(0, 1);
    s.erase(s.begin());
    return temp;
}

template <typename T>
void testTraceDFA(DFA<T> m, int count) {
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
void testNoTraceDFA(DFA<T> m, int count) {
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
    if (accepted)
        cout << "\tAccepted\t";
    else
        cout << "\tRejected\t";
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
Str searchAlgo(DFA<T> m, T qi, vector<T> *visited, Str output) {
    vector<Character> E = m.getAlpha().getAlphabetVector();
    if (m.accepts(output))
        return output;

    for (int i = 0; i < (int)E.size(); i++) {
        auto qNext = m.getTransitions()(qi, E.at(i));
        auto it = find(visited->begin(), visited->end(), qNext);
        // if we haven't visited qNext, put qNext in visited, update output, recursive call
        if (it == visited->end()) {
            visited->push_back(qNext);
            output.pushBack(E.at(i));
            output = searchAlgo(m, qNext, visited, output);
            if (output.getSize() > 0)
                return output;
        }
    }
    return output;
}

template <typename T>
optional<Str> possibleString(DFA<T> m) {
    vector<T> visited{m.getStartState()};
    Str output;
    output = searchAlgo(m, m.getStartState(), &visited, output);

    if (m.accepts(output))
        return output;
    return nullopt;
}

// Task 13 - (Complement) Write a function that takes one DFA and returns a DFA that accepts what the given one doesn't (and vice versa).
template <typename T>
DFA<T> complementDFA(DFA<T> m) {
    auto F = m.getAcceptingStates();
    auto fPrime = [=](T qi) { return !F(qi); };
    return DFA<T>(m.getStates(), m.getAlpha(), m.getStartState(), m.getTransitions(), fPrime);
}

// Task 14 - (Union) Write a function that takes two DFAs and returns a third DFA that accepts a string that either DFA accepts.
template <typename F, typename G>
DFA<pair<F, G>> unionDFAs(DFA<F> m1, DFA<G> m2) {
    function<bool(F)> Q1 = m1.getStates();
    function<bool(G)> Q2 = m2.getStates();
    function<F(F, Character)> D1 = m1.getTransitions();
    function<G(G, Character)> D2 = m2.getTransitions();
    function<bool(F)> A1 = m1.getAcceptingStates();
    function<bool(G)> A2 = m2.getAcceptingStates();

    return DFA<pair<F, G>>([Q1, Q2](pair<F, G> state) { return Q1(state.first) && Q2(state.second); },
                                m1.getAlpha(), pair<F, G>{m1.getStartState(), m2.getStartState()},
                                [D1, D2](pair<F, G> state, Character c) {
                                    F q1 = D1(state.first, c);
                                    G q2 = D2(state.second, c);
                                    return pair<F, G>{q1, q2};
                                },
                                [A1, A2](pair<F, G> state) { return A1(state.first) || A2(state.second); });
}

// Task 16 - (Intersect) Write a function that takes two DFAs and returns a third DFA that accepts a string if both arguments accepts it.
template <typename F, typename G>
DFA<pair<F, G>> intersectDFAs(DFA<F> m1, DFA<G> m2) {
    function<bool(F)> Q1 = m1.getStates();
    function<bool(G)> Q2 = m2.getStates();
    function<F(F, Character)> D1 = m1.getTransitions();
    function<G(G, Character)> D2 = m2.getTransitions();
    function<bool(F)> A1 = m1.getAcceptingStates();
    function<bool(G)> A2 = m2.getAcceptingStates();

    return DFA<pair<F, G>>([Q1, Q2](pair<F, G> state) { return Q1(state.first) && Q2(state.second); },
                                m1.getAlpha(), pair<F, G>{m1.getStartState(), m2.getStartState()},
                                [D1, D2](pair<F, G> state, Character c) {
                                    F q1 = D1(state.first, c);
                                    G q2 = D2(state.second, c);
                                    return pair<F, G>{q1, q2};
                                },
                                [A1, A2](pair<F, G> state) { return A1(state.first) && A2(state.second); });
}

// Task 18 - (Subset) Write a function which takes two DFAs (X and Y) and returns whether every string accepted by X is also accepted by Y.
template <typename T1, typename T2>
bool subset(DFA<T1> X, DFA<T2> Y) { return !possibleString(intersectDFAs(complementDFA(Y), X)).has_value(); }

// Task 20 - (Equality) Write a function which takes two DFAs (X and Y) and returns whether every string accepted by X is also accepted by Y and vice versa.
template <typename T1, typename T2>
bool isEqual(DFA<T1> X, DFA<T2> Y) { return subset(X, Y) && subset(Y, X); }

// Task 24 - Convert DFA to NFA
template <typename T>
NFA<T> convertDFA(DFA<T> m) {
    auto dPrime = [=](T state, Character c) { return c.getCharacterValue().empty() ? vector<T>{} : vector<T>{m.d(state, c)}; };
    return NFA<T>(m.Q, m.q0, dPrime, m.F);
}

// Task 27 - (Oracle) determines if the trace is a valid execution of the NFA and accepts results in the given boolean.
template <typename T>
bool oracle(NFA<T> m, vector<pair<T, string>> trace) {
    if (trace.size() == 0) return true;

    for (unsigned int i = 1; i < trace.size(); i++) {
        string currentString = trace[i - 1].second;
        string nextString = trace[i].second;
        auto c(currentString.at(0));
        auto currentState = trace[i - 1].first;
        auto nextState = trace[i].first;

        // if the current string isn't empty, erase the first char of the string
        if (!currentString.empty())
            currentString.erase(currentString.begin());

        // Character transitions vector
        auto charVect = m.d(trace[i - 1].first, c);

        // if the current string equals next string
        if (trace[i - 1].second == nextString) {
            //epsilon transitions vector
            auto epsVect = m.d(currentState, Character(""));

            // return false if nextState isn't in the epsilon transition vector
            if (find(epsVect.begin(), epsVect.end(), nextState) == epsVect.end())
                return false;

            // if the current string isn't equal to the next string, or
            // if the next state isn't in the character transition vector, return false
        } else if (currentString != nextString) {
            return false;
        } else if (find(charVect.begin(), charVect.end(), nextState) == charVect.end())
            return false;
    }
    return true;
}

// Task 32 - (Backtracking)
template <typename T>
bool backtracking(NFA<T> nfa, Str str) { return backtrack_help(nfa, str, nfa.q0); }

template <typename T>
bool backtrack_help(NFA<T> nfa, Str str, T qi) {
    vector<T> epsVect = nfa.d(qi, Character("\u03B5"));

    // for all the epsilon transitions in epsVect, if any of them return true
    // then we're done, and backtrack returns true
    for (auto i : epsVect)
        if (backtrack_help(nfa, str, i))
            return true;

    // if the input string isn't empty
    if (!str.isEmpty()) {
        Character ch = str.getStr().front();
        vector<T> charVect = nfa.d(qi, ch);
        str.eraseFront();

        // for all the character transitions in charVect, if any of them return true
        // then we're done, and backtrack returns true
        for (auto i : charVect)
            if (backtrack_help(nfa, str, i))
                return true;
    } else
        return nfa.F(qi);

    return false;
}

// Task 33 - (Union)
template <typename T1, typename T2>
NFA<pair<int, pair<optional<T1>, optional<T2>>>> unionNFAs(NFA<T1> nfa1, NFA<T2> nfa2) {
    // New start state
    pair<int, pair<optional<T1>, optional<T2>>> q0 = {0, {nullopt, nullopt}};

    // New Set of States
    function<bool(pair<int, pair<optional<T1>, optional<T2>>>)> Q =
        [=](pair<int, pair<optional<T1>, optional<T2>>> qi) {
            if (qi == q0)
                return true;

            // Left Side, NFA 1
            else if (qi.first == 1 && qi.second.first != nullopt)
                return nfa1.Q(qi.second.first.value());

            // Right Side, NFA 2
            else if (qi.first == 2 && qi.second.second != nullopt)
                return nfa2.Q(qi.second.second.value());

            return false;
        };

    // New Set of Delta Transitions
    function<vector<pair<int, pair<optional<T1>, optional<T2>>>>(
        pair<int, pair<optional<T1>, optional<T2>>>, Character)>
        delta = [=](pair<int, pair<optional<T1>, optional<T2>>> qi, Character c) {
            vector<pair<int, pair<optional<T1>, optional<T2>>>> transVect;

            // if we're at the new beginning state and epsilon is given
            if (qi == q0 && c.getCharacterValue() == "\u03B5") {
                transVect.push_back({1, {nfa1.q0, nullopt}});
                transVect.push_back({2, {nullopt, nfa2.q0}});

                // Left Side, first NFA
            } else if (qi.first == 1 && qi.second.first.has_value()) {
                // Get all of the epsilon transitions from NFA 1
                vector<T1> epsVect = nfa1.d(qi.second.first.value(), Character("\u03B5"));
                for (auto i : epsVect)
                    transVect.push_back({1, {i, nullopt}});

                // Get all of the character transitions from NFA 1
                vector<T1> charVect = nfa1.d(qi.second.first.value(), c);
                for (auto i : charVect)
                    transVect.push_back({1, {i, nullopt}});

                // Right Side, second NFA
            } else if (qi.first == 2 && qi.second.second.has_value()) {
                // Get all of the epsilon transitions from NFA 2
                vector<T2> epsVect = nfa2.d(qi.second.second.value(), Character("\u03B5"));
                for (auto i : epsVect)
                    transVect.push_back({2, {nullopt, i}});

                // Get all of the character transitions from NFA 2
                vector<T2> charVect = nfa2.d(qi.second.second.value(), c);
                for (auto i : charVect)
                    transVect.push_back({2, {nullopt, i}});
            }
            return transVect;
        };

    // New Set of Accepting States
    function<bool(pair<int, pair<optional<T1>, optional<T2>>>)> F =
        [=](pair<int, pair<optional<T1>, optional<T2>>> qi) {
            // Return accept status of NFA 1 if input state has a value
            if (qi.first == 1 && qi.second.first != nullopt)
                return nfa1.F(qi.second.first.value());

            // Return accept status of NFA 2 if input state has a value
            else if (qi.first == 2 && qi.second.second != nullopt)
                return nfa2.F(qi.second.second.value());

            return false;
        };

    return NFA<pair<int, pair<optional<T1>, optional<T2>>>>(Q, q0, delta, F);
}

// Task 34 - (Concatenation)
template <typename T1, typename T2>
NFA<pair<int, pair<optional<T1>, optional<T2>>>> concatNFAs(NFA<T1> nfa1, NFA<T2> nfa2) {
    pair<int, pair<optional<T1>, optional<T2>>> q0 = {0, {nullopt, nullopt}};

    // New Set of States
    function<bool(pair<int, pair<optional<T1>, optional<T2>>>)> Q =
        [=](pair<int, pair<optional<T1>, optional<T2>>> qi) {
            if (qi == q0)
                return true;

            // Left Side
            else if (qi.first == 1 && qi.second.first != nullopt)
                return nfa1.Q(qi.second.first.value());

            // Right Side
            else if (qi.first == 2 && qi.second.second != nullopt)
                return nfa2.Q(qi.second.second.value());

            return false;
        };

    // New Set of Delta Transitions
    function<vector<pair<int, pair<optional<T1>, optional<T2>>>>(
        pair<int, pair<optional<T1>, optional<T2>>>, Character)>
        delta = [=](pair<int, pair<optional<T1>, optional<T2>>> qi, Character c) {
            vector<pair<int, pair<optional<T1>, optional<T2>>>> transVect;

            if (qi == q0 && c.getCharacterValue() == "\u03B5")
                transVect.push_back({1, {nfa1.q0, nullopt}});

            else if (qi.first == 1 && qi.second.first.has_value()) {
                vector<T1> epsVect = nfa1.d(qi.second.first.value(), Character("\u03B5"));
                for (auto i : epsVect) {
                    transVect.push_back({1, {i, nullopt}});
                    if (nfa1.F((i))) transVect.push_back({2, {nullopt, nfa2.q0}});
                }

                vector<T1> charVect = nfa1.d(qi.second.first.value(), c);
                for (auto i : charVect) {
                    transVect.push_back({1, {i, nullopt}});
                    if (nfa1.F((i))) transVect.push_back({2, {nullopt, nfa2.q0}});
                }

            } else if (qi.first == 2 && qi.second.second.has_value()) {
                vector<T2> epsVect = nfa2.d(qi.second.second.value(), Character("\u03B5"));
                for (auto i : epsVect)
                    transVect.push_back({2, {nullopt, i}});

                vector<T2> charVect = nfa2.d(qi.second.second.value(), c);
                for (auto i : charVect)
                    transVect.push_back({2, {nullopt, i}});
            }
            return transVect;
        };

    // New Set of Accepting States
    function<bool(pair<int, pair<optional<T1>, optional<T2>>>)> F =
        [=](pair<int, pair<optional<T1>, optional<T2>>> qi) {
            // Return accept status of NFA 2 if input state has a value
            if (qi.first == 2 && qi.second.second != nullopt)
                return nfa2.F(qi.second.second.value());

            return false;
        };

    return NFA<pair<int, pair<optional<T1>, optional<T2>>>>(Q, q0, delta, F);
}

// Task 36 - (Kleene Star)
template <typename T>
NFA<T> kleeneStar(NFA<T> N) {

    // new start state
    T q0 = 0;

    // new set of states
    function<bool(T)> Q = [=](T qi) { return (N.Q(qi) || qi == q0); };

    // new set of delta transitions
    function<vector<T>(T, Character)> d = [=](T qi, Character c) {
        vector<T> transVector = N.d(qi, c);

        if (qi == q0)
            transVector.push_back(N.q0);
        else if (N.F(qi))
            transVector.push_back(q0);
        return transVector;
    };

    // new set of accepting states
    function<bool(T)> F = [=](T qi) { return (N.F(qi) || qi == q0); };

    return NFA<T>(Q, q0, d, F);
}

// Task 38 - Write a function which converts an NFA into a DFA that accepts the same language.
template <typename T>
DFA<std::vector<T>> convertNFA(NFA<T> input, Alphabet alpha) {

    // set of NFA states
    auto Qn = input.Q;

    // set of DFA states
    auto Qd = [=](std::vector<T> state) {
        std::vector<T> found;
        for (int i = 0; i < (int)state.size(); i++) {
            if (Qn(state.at(i))) {
                for (int j = 0; j < (int)found.size(); j++)
                    if (state.at(i) == found.at(j))
                        return false;
                found.push_back(state.at(i));
            } else
                return false;
        }
        return true;
    };

    // set of NFA transitions
    auto Dn = input.d;

    // epsilon transitions
    auto E = [=](std::vector<T> input) {
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i < (int)input.size(); i++) {
                std::vector<T> temp = Dn(input.at(i), Character(""));
                for (int j = 0; j < (int)temp.size(); j++)
                    if (std::find(input.begin(), input.end(), temp.at(j)) == input.end()) {
                        changed = true;
                        input.push_back(temp.at(j));
                    }
            }
        }
        return input;
    };

    // new start state - the set containing only the input NFAs start state
    std::vector<T> startState = {input.q0};
    startState = E(startState);

    // set of NFA accepting states
    auto Fn = input.F;

    // set of DFA accepting states
    auto Fd = [=](std::vector<T> state) {
        for (int i = 0; i < (int)state.size(); i++)
            if (Fn(state.at(i)))
                return true;
        return false;
    };

    // set of DFA transitions
    auto Dd = [=](std::vector<T> state, Character c) {
        std::vector<T> check;
        for (int i = 0; i < (int)state.size(); i++) {
            std::vector<T> temp = Dn(state.at(i), c);
            check.insert(check.end(), temp.begin(), temp.end());
        }

        for (int i = 0; i < (int)check.size(); i++)
            for (int j = 0; j < (int)check.size(); j++)
                if (check.at(i) == check.at(j) && i != j)
                    check.erase(check.begin() + j);
        return E(check);
    };

    // build the new DFA and return it
    DFA<std::vector<T>> newDFA(Qd, alpha, startState, Dd, Fd);
    return newDFA;
}

void runTestCases() {
    Alphabet binaryAlpha;
    binaryAlpha.setAlphaVector(vector<Character>{Character("0"), Character("1")});
    Alphabet abAlpha;
    abAlpha.setAlphaVector(vector<Character>{Character("a"), Character("b")});
    Alphabet alexAlpha;
    alexAlpha.setAlphaVector(vector<Character>{Character("A"), Character("L"), Character("E"), Character("X")});
    Alphabet unaryAlpha;
    unaryAlpha.setAlphaVector(vector<Character>{Character("0")});
    string divider = "\n====================================================================\n";

    {  // DFAs Initialized Below, Test Calls At The Bottom

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
        DFA<int> alexDFA([](int qi) { return qi == 0 || qi == 1 || qi == 2 || qi == 3 || qi == 4; }, alexAlpha, 0,
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

        cout << divider << "[1] ACCEPTS NO STRINGS" << divider;
        testTraceDFA(noString, 12);

        cout << divider << "[2] ACCEPT ONLY EMPTY STRING" << divider;
        testTraceDFA(emptyString, 12);
        testNoTraceDFA(unionDFAs(emptyString, noString), 12);

        cout << divider << "[3] FUNCTION RETURNS A DFA THAT ONLY ACCEPTS GIVEN CHARACTER (TASK 7)" << divider;
        testTraceDFA(task7DFA, 5);

        cout << divider << "[4] STRINGS OF EVEN LENGTH" << divider;
        testTraceDFA(evenLength, 12);
        testNoTraceDFA(unionDFAs(complementDFA(evenLength), emptyString), 12);
        testNoTraceDFA(intersectDFAs(evenLength, emptyString), 12);

        cout << divider << "[5] STRINGS OF EVEN BINARY NUMBERS" << divider;
        testTraceDFA(evenBinary, 12);
        testNoTraceDFA(unionDFAs(evenLength, evenBinary), 12);
        testNoTraceDFA(intersectDFAs(evenLength, evenBinary), 12);
        testNoTraceDFA(intersectDFAs(evenLength, evenBinary), 12);
        testNoTraceDFA(intersectDFAs(complementDFA(evenLength), evenBinary), 12);
        testNoTraceDFA(intersectDFAs(evenLength, complementDFA(evenBinary)), 12);

        cout << divider << "[6] BOOK FIGURE 1.12" << divider;
        testTraceDFA(bookFigure112, 12);

        cout << divider << "[7] ONLY ACCEPT IF STRING ENDS IN A 1" << divider;
        testTraceDFA(endsIn1, 12);
        testNoTraceDFA(unionDFAs(endsIn1, evenBinary), 12);
        testNoTraceDFA(unionDFAs(endsIn1, evenLength), 12);
        testNoTraceDFA(intersectDFAs(endsIn1, evenLength), 12);
        testNoTraceDFA(intersectDFAs(endsIn1, evenLength), 12);

        cout << divider << "[8] ONLY ACCEPT IF STRING CONTAINS AN ODD NUMBER OF 1s (BOOK FIGURE 1.20)" << divider;
        testTraceDFA(bookFigure120, 12);
        testTraceDFA(complementDFA(bookFigure120), 12);

        cout << divider << "[9] ONLY ACCEPT IF ALEX IS A SUBSTRING" << divider;
        testTraceDFA(alexDFA, 12);
        testTraceDFA(complementDFA(alexDFA), 12);

        cout << divider << "TASK 18 & 19 - SUBSET TESTS" << divider;
        cout << "\nsubset(endsIn1, evenLength)\t\t  :\t" << subset(endsIn1, evenLength);
        cout << "\nsubset(evenLength, endsIn1)\t\t  :\t" << subset(evenLength, endsIn1);
        cout << "\nsusbset(evenBinary, emptyString)\t  :\t" << subset(evenBinary, emptyString);
        cout << "\nsusbset(evenLength, emptyString)\t  :\t" << subset(evenLength, emptyString);
        cout << endl;
        cout << "\nsusbset(emptyString, evenBinary)\t  :\t" << subset(emptyString, evenBinary);
        cout << "\nsusbset(emptyString, evenLength)\t  :\t" << subset(emptyString, evenLength);
        cout << "\nsusbset(noString, emptyString)\t\t  :\t" << subset(noString, emptyString);
        cout << "\nsusbset(emptyString, noString)\t\t  :\t" << subset(noString, emptyString);
        cout << "\nsusbset(alexDFA, complementDFA(noString)) :\t" << subset(alexDFA, complementDFA(noString));

        {  // Task 21 & 22 - Equality Tests & Verifying Union, Intersect, Complement - Commented out for Checkpoint 4
            cout << "\n\n"
                 << divider << "TASK 21 & 22 - EQUALITY TESTS & VERIFYING UNION, INTERSECT, COMPLEMENT" << divider;
            cout << "\n----- FALSE EXPECTED -----";
            cout << "\nTest [1]  \t :\t" << isEqual(endsIn1, evenLength);
            cout << "\nTest [2]  \t :\t" << isEqual(bookFigure120, bookFigure112);
            cout << "\nTest [3]  \t :\t" << isEqual(noString, emptyString);
            cout << "\nTest [4]  \t :\t" << isEqual(noString, evenLength);
            cout << "\nTest [5]  \t :\t" << isEqual(intersectDFAs(noString, emptyString), emptyString);
            cout << "\nTest [6]  \t :\t" << isEqual(intersectDFAs(evenLength, complementDFA(evenLength)), complementDFA(noString));
            cout << endl;
            cout << "\n----- TRUE EXPECTED -----";
            cout << "\nTest [7]  \t :\t" << isEqual(noString, noString);
            cout << "\nTest [8]  \t :\t" << isEqual(emptyString, emptyString);
            cout << "\nTest [9]  \t :\t" << isEqual(alexDFA, alexDFA);
            cout << "\nTest [10]  \t :\t" << isEqual(unionDFAs(noString, emptyString), emptyString);
            cout << "\nTest [11]  \t :\t" << isEqual(unionDFAs(complementDFA(noString), alexDFA), complementDFA(noString));
            cout << "\nTest [12]  \t :\t" << isEqual(unionDFAs(evenLength, complementDFA(evenLength)), complementDFA(noString));
            cout << "\nTest [13]  \t :\t" << isEqual(unionDFAs(emptyString, complementDFA(emptyString)), complementDFA(noString));
            cout << "\nTest [14]  \t :\t" << isEqual(unionDFAs(noString, emptyString), intersectDFAs(complementDFA(noString), emptyString));
            cout << "\nTest [15]  \t :\t" << isEqual(intersectDFAs(emptyString, complementDFA(emptyString)), noString);
            cout << "\nTest [16]  \t :\t" << isEqual(intersectDFAs(complementDFA(noString), alexDFA), alexDFA);
        }

        auto emptyNFA = convertDFA(emptyString);
    }

    {      // NFAs
        {  // Tasks 25+

            // Book Figure 1.27
            NFA<int> nfa1([](int qi) { return qi == 1 || qi == 2 || qi == 3 || qi == 4; }, 1,
                          [](int qi, Character c) {
                              vector<int> possibleTrans;
                              switch (qi) {
                                  case 1:
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(1);
                                      if (c.getCharacterValue() == "1") {
                                          possibleTrans.push_back(1);
                                          possibleTrans.push_back(2);
                                      }
                                      break;
                                  case 2:
                                      if (c.getCharacterValue() == "\u03B5") possibleTrans.push_back(3);
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(3);
                                      break;
                                  case 3:
                                      if (c.getCharacterValue() == "1") possibleTrans.push_back(4);
                                      break;
                                  case 4:
                                      if (c.getCharacterValue() == "0" || c.getCharacterValue() == "1")
                                          possibleTrans.push_back(4);
                                      break;
                              }
                              return possibleTrans;
                          },
                          [](int qi) { return qi == 4; });

            // Book Figure 1.31
            NFA<int> nfa2([](int qi) { return qi == 1 || qi == 2 || qi == 3 || qi == 4; }, 1,
                          [](int qi, Character c) {
                              vector<int> possibleTrans;
                              if (c.getCharacterValue().empty()) return possibleTrans;

                              switch (qi) {
                                  case 1:
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(1);
                                      if (c.getCharacterValue() == "1") {
                                          possibleTrans.push_back(1);
                                          possibleTrans.push_back(2);
                                      }
                                      break;
                                  case 2:
                                      if (c.getCharacterValue() == "0" || c.getCharacterValue() == "1") possibleTrans.push_back(3);
                                      break;
                                  case 3:
                                      if (c.getCharacterValue() == "0" || c.getCharacterValue() == "1") possibleTrans.push_back(4);
                                      break;
                              }
                              return possibleTrans;
                          },
                          [](int qi) { return qi == 4; });

            // Book Figure 1.34
            NFA<int> nfa3([](int qi) { return qi >= 1 || qi <= 6; }, 1,
                          [](int qi, Character c) {
                              vector<int> possibleTrans;

                              switch (qi) {
                                  case 1:
                                      if (c.getCharacterValue() == "\u03B5") {
                                          possibleTrans.push_back(2);
                                          possibleTrans.push_back(3);
                                      }

                                      break;
                                  case 2:
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(4);
                                      break;
                                  case 3:
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(5);
                                      break;
                                  case 4:
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(2);
                                      break;
                                  case 5:
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(6);
                                      break;
                                  case 6:
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(3);
                                      break;
                              }
                              return possibleTrans;
                          },
                          [](int qi) { return qi == 2 || qi == 3; });

            // Book Figure 1.36
            NFA<int> nfa4([](int qi) { return qi == 1 || qi == 2 || qi == 3; }, 1,
                          [](int qi, Character c) {
                              vector<int> possibleTrans;
                              switch (qi) {
                                  case 1:
                                      if (c.getCharacterValue() == "\u03B5") possibleTrans.push_back(3);
                                      if (c.getCharacterValue() == "b") possibleTrans.push_back(2);
                                      break;
                                  case 2:
                                      if (c.getCharacterValue() == "a") {
                                          possibleTrans.push_back(2);
                                          possibleTrans.push_back(3);
                                      }
                                      if (c.getCharacterValue() == "b") possibleTrans.push_back(3);
                                      break;
                                  case 3:
                                      if (c.getCharacterValue() == "a") possibleTrans.push_back(1);
                                      break;
                              }
                              return possibleTrans;
                          },
                          [](int qi) { return qi == 1; });

            // Custom NFA alternates between 0 and 1. Accepted examples: 010, 01010, 0101010
            NFA<int> nfa5([](int qi) { return qi >= 1 && qi <= 5; }, 1,
                          [](int qi, Character c) {
                              vector<int> possibleTrans;

                              switch (qi) {
                                  case 1:
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(2);
                                      break;
                                  case 2:
                                      if (c.getCharacterValue() == "1") possibleTrans.push_back(3);
                                      break;
                                  case 3:
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(4);
                                      break;
                                  case 4:
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(5);
                                      if (c.getCharacterValue() == "1") {
                                          possibleTrans.push_back(1);
                                          possibleTrans.push_back(3);
                                      }
                                      break;
                                  case 5:
                                      if (c.getCharacterValue() == "0" || c.getCharacterValue() == "1") possibleTrans.push_back(5);
                                      break;
                              }
                              return possibleTrans;
                          },
                          [](int qi) { return qi == 4; });

            // Custom NFA
            NFA<int> nfa6([](int qi) { return qi >= 1 && qi <= 5; }, 1,
                          [](int qi, Character c) {
                              vector<int> possibleTrans;

                              switch (qi) {
                                  case 1:
                                      if (c.getCharacterValue() == "\u03B5") {
                                          possibleTrans.push_back(2);
                                          possibleTrans.push_back(3);
                                      }
                                      break;
                                  case 2:
                                      if (c.getCharacterValue() == "\u03B5") possibleTrans.push_back(4);
                                      break;
                                  case 3:
                                      if (c.getCharacterValue() == "\u03B5") possibleTrans.push_back(5);
                                      break;
                                  case 4:
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(4);
                                      break;
                                  case 5:
                                      if (c.getCharacterValue() == "0") possibleTrans.push_back(5);
                                      break;
                              }
                              return possibleTrans;
                          },
                          [](int qi) { return qi == 4 && qi == 5; });

            {   // Task 26 Manually Write Traces (With Oracle Testing).
                cout << "\n\n"
                     << divider << "TASK 26 - TRACE BEHAVIOR WITH ORACLE TESTING" << divider;

                cout << "\n----- TRUE EXPECTED -----";

                vector<pair<int, string>> traceVectorNfa1_1{
                    pair<int, string>(1, "101"),
                    pair<int, string>(2, "01"),
                    pair<int, string>(3, "1"),
                    pair<int, string>(4, "")};

                vector<pair<int, string>> traceVectorNfa1_2{
                    pair<int, string>(1, "0011"),
                    pair<int, string>(1, "011"),
                    pair<int, string>(1, "11"),
                    pair<int, string>(2, "1"),
                    pair<int, string>(3, "1"),
                    pair<int, string>(4, "")};

                vector<pair<int, string>> traceVectorNfa1_3{
                    pair<int, string>(1, "11"),
                    pair<int, string>(2, "1"),
                    pair<int, string>(3, "1"),
                    pair<int, string>(4, "")};

                vector<pair<int, string>> traceVectorNfa1_4{
                    pair<int, string>(1, "")};

                cout << "\nTest[1-1] \t : \t" << oracle(nfa1, traceVectorNfa1_1) << endl;
                cout << "Test[1-2] \t : \t" << oracle(nfa1, traceVectorNfa1_2) << endl;
                cout << "Test[1-3] \t : \t" << oracle(nfa1, traceVectorNfa1_3) << endl;
                cout << "Test[1-4] \t : \t" << oracle(nfa1, traceVectorNfa1_4) << endl;

                vector<pair<int, string>> traceVectorNfa2_1{
                    pair<int, string>(1, "101"),
                    pair<int, string>(2, "01"),
                    pair<int, string>(3, "1"),
                    pair<int, string>(4, "")};

                vector<pair<int, string>> traceVectorNfa2_2{
                    pair<int, string>(1, "0111"),
                    pair<int, string>(1, "111"),
                    pair<int, string>(2, "11"),
                    pair<int, string>(3, "1"),
                    pair<int, string>(4, "")};

                vector<pair<int, string>> traceVectorNfa2_3{
                    pair<int, string>(1, "1"),
                    pair<int, string>(1, "")};

                vector<pair<int, string>> traceVectorNfa2_4{
                    pair<int, string>(1, "")};

                cout << "\nTest[2-1] \t : \t" << oracle(nfa2, traceVectorNfa2_1) << endl;
                cout << "Test[2-2] \t : \t" << oracle(nfa2, traceVectorNfa2_2) << endl;
                cout << "Test[2-3] \t : \t" << oracle(nfa2, traceVectorNfa2_3) << endl;
                cout << "Test[2-4] \t : \t" << oracle(nfa2, traceVectorNfa2_4) << endl;

                vector<pair<int, string>> traceVectorNfa3_1{
                    pair<int, string>(1, "0000"),
                    pair<int, string>(2, "0000"),
                    pair<int, string>(4, "000"),
                    pair<int, string>(2, "00"),
                    pair<int, string>(4, "0")};

                vector<pair<int, string>> traceVectorNfa3_2{
                    pair<int, string>(1, "0000"),
                    pair<int, string>(3, "0000"),
                    pair<int, string>(5, "000"),
                    pair<int, string>(6, "00"),
                    pair<int, string>(3, "0")};

                vector<pair<int, string>> traceVectorNfa3_3{
                    pair<int, string>(1, "0"),
                    pair<int, string>(3, "0"),
                    pair<int, string>(5, "")};

                vector<pair<int, string>> traceVectorNfa3_4{
                    pair<int, string>(1, "0"),
                    pair<int, string>(2, "0"),
                    pair<int, string>(4, "")};

                cout << "\nTest[3-1] \t : \t" << oracle(nfa3, traceVectorNfa3_1) << endl;
                cout << "Test[3-2] \t : \t" << oracle(nfa3, traceVectorNfa3_2) << endl;
                cout << "Test[3-3] \t : \t" << oracle(nfa3, traceVectorNfa3_3) << endl;
                cout << "Test[3-4] \t : \t" << oracle(nfa3, traceVectorNfa3_4) << endl;

                vector<pair<int, string>> traceVectorNfa4_1{
                    pair<int, string>(1, "abba"),
                    pair<int, string>(3, "abba"),
                    pair<int, string>(1, "bba"),
                    pair<int, string>(2, "ba"),
                    pair<int, string>(3, "a"),
                    pair<int, string>(1, "")};

                vector<pair<int, string>> traceVectorNfa4_2{
                    pair<int, string>(1, "baab"),
                    pair<int, string>(2, "aab"),
                    pair<int, string>(2, "ab"),
                    pair<int, string>(3, "b")};

                vector<pair<int, string>> traceVectorNfa4_3{
                    pair<int, string>(1, "b"),
                    pair<int, string>(3, "b")};

                vector<pair<int, string>> traceVectorNfa4_4{
                    pair<int, string>(1, "b"),
                    pair<int, string>(2, "")};

                cout << "\nTest[4-1] \t : \t" << oracle(nfa4, traceVectorNfa4_1) << endl;
                cout << "Test[4-2] \t : \t" << oracle(nfa4, traceVectorNfa4_2) << endl;
                cout << "Test[4-3] \t : \t" << oracle(nfa4, traceVectorNfa4_3) << endl;
                cout << "Test[4-4] \t : \t" << oracle(nfa4, traceVectorNfa4_4) << endl;

                vector<pair<int, string>> traceVectorNfa5_1{
                    pair<int, string>(1, "010"),
                    pair<int, string>(2, "10"),
                    pair<int, string>(3, "0"),
                    pair<int, string>(4, "")};

                vector<pair<int, string>> traceVectorNfa5_2{
                    pair<int, string>(1, "01010"),
                    pair<int, string>(2, "1010"),
                    pair<int, string>(3, "010"),
                    pair<int, string>(4, "10"),
                    pair<int, string>(1, "0"),
                    pair<int, string>(2, "")};

                vector<pair<int, string>> traceVectorNfa5_3{
                    pair<int, string>(1, "0"),
                    pair<int, string>(2, "")};

                vector<pair<int, string>> traceVectorNfa5_4{
                    pair<int, string>(1, "01"),
                    pair<int, string>(2, "1"),
                    pair<int, string>(3, "")};

                cout << "\nTest[5-1] \t : \t" << oracle(nfa5, traceVectorNfa5_1) << endl;
                cout << "Test[5-2] \t : \t" << oracle(nfa5, traceVectorNfa5_2) << endl;
                cout << "Test[5-3] \t : \t" << oracle(nfa5, traceVectorNfa5_3) << endl;
                cout << "Test[5-4] \t : \t" << oracle(nfa5, traceVectorNfa5_4) << endl;

                vector<pair<int, string>> traceVectorNfa6_1{
                    pair<int, string>(1, "")};

                vector<pair<int, string>> traceVectorNfa6_2{
                    pair<int, string>(1, "0"),
                    pair<int, string>(2, "0"),
                    pair<int, string>(4, "0"),
                    pair<int, string>(4, "")};

                vector<pair<int, string>> traceVectorNfa6_3{
                    pair<int, string>(1, "00"),
                    pair<int, string>(2, "00"),
                    pair<int, string>(4, "00"),
                    pair<int, string>(4, "0"),
                    pair<int, string>(4, "")};

                vector<pair<int, string>> traceVectorNfa6_4{
                    pair<int, string>(1, "00"),
                    pair<int, string>(3, "00"),
                    pair<int, string>(5, "00"),
                    pair<int, string>(5, "0"),
                    pair<int, string>(5, "")};

                cout << "\nTest[6-1] \t : \t" << oracle(nfa6, traceVectorNfa6_1) << endl;
                cout << "Test[6-2] \t : \t" << oracle(nfa6, traceVectorNfa6_2) << endl;
                cout << "Test[6-3] \t : \t" << oracle(nfa6, traceVectorNfa6_3) << endl;
                cout << "Test[6-4] \t : \t" << oracle(nfa6, traceVectorNfa6_4);
            }

            {
            {   // Tasks 29 & 31  - Trace Tree Tests (Low number of tests due to terminal space)
                         cout << "\n\n"
                              << divider << "TASK 29 & 31 - TRACE TREE BEHAVIOR" << divider;
                    TraceTree<int> test;
                    cout << "\n\nNFA 1 | Str(10)" << divider;
                    test.printTree(test.explore(nfa1, Str("10")), 0);
                    cout << "\n\nNFA 1 | Str(101)" << divider;
                    test.printTree(test.explore(nfa1, Str("101")), 0);

                    cout << "\n\nNFA 2 | Str(111)" << divider;
                    test.printTree(test.explore(nfa2, Str("111")), 0);
                    cout << "\n\nNFA 2 | Str(00)" << divider;
                    test.printTree(test.explore(nfa2, Str("00")), 0);

                    cout << "\n\nNFA 3 | Str()" << divider;
                    test.printTree(test.explore(nfa3, Str("")), 0);
                    cout << "\n\nNFA 3 | Str(0)" << divider;
                    test.printTree(test.explore(nfa3, Str("0")), 0);
                    cout << "\n\nNFA 3 | Str(00)" << divider;
                    test.printTree(test.explore(nfa3, Str("00")), 0);

                    cout << "\n\nNFA 4 | Str(abb)" << divider;
                    test.printTree(test.explore(nfa4, Str("abb")), 0);
                    cout << "\n\nNFA 4 | Str(baa)" << divider;
                    test.printTree(test.explore(nfa4, Str("baa")), 0);

                    cout << "\n\nNFA 5 | Str(010)" << divider;
                    test.printTree(test.explore(nfa5, Str("010")), 0);
                    cout << "\n\nNFA 5 | Str(baa)" << divider;
                    test.printTree(test.explore(nfa5, Str("01010")), 0);

                    cout << "\n\nNFA 6 | Str()" << divider;
                    test.printTree(test.explore(nfa6, Str("")), 0);
                    cout << "\n\nNFA 6 | Str(00)" << divider;
                    test.printTree(test.explore(nfa6, Str("00")), 0);
            }
            }

            {  // Task 32 - Backtracking Tests
                cout << "\n\n"
                    << divider << "TASK 32 - (BACKTRACKING)" << divider;
                cout << "\n----- FALSE EXPECTED -----";
                cout << "\nTest[1] \t : \t" << backtracking(nfa1, Str("000"));
                cout << "\nTest[2] \t : \t" << backtracking(nfa2, Str("0011"));
                cout << "\nTest[3] \t : \t" << backtracking(nfa3, Str("0"));
                cout << "\nTest[4] \t : \t" << backtracking(nfa4, Str("bab"));
                cout << "\nTest[5] \t : \t" << backtracking(nfa5, Str("01"));
                cout << "\nTest[6] \t : \t" << backtracking(nfa6, Str("1"));

                cout << "\n\n----- TRUE EXPECTED -----";
                cout << "\nTest[7] \t : \t" << backtracking(nfa1, Str("111"));
                cout << "\nTest[8] \t : \t" << backtracking(nfa2, Str("111"));
                cout << "\nTest[9] \t : \t" << backtracking(nfa3, Str("00"));
                cout << "\nTest[10] \t : \t" << backtracking(nfa4, Str("baa"));
                cout << "\nTest[11] \t : \t" << backtracking(nfa5, Str("010"));
            }

            {  // Task 33 - Union Tests
                cout << "\n\n"
                    << divider << "TASK 33 - (UNION NFAs TESTING)" << divider;

                auto nfaUnionTest1 = unionNFAs(nfa1, nfa3);
                auto nfaUnionTest2 = unionNFAs(nfa1, nfa2);
                auto nfaUnionTest3 = unionNFAs(nfa4, nfa5);

                cout << "\n----- FALSE EXPECTED -----";

                cout << "\nTest[1] \t : \t" << backtracking(nfaUnionTest1, Str("10"));
                cout << "\nTest[2] \t : \t" << backtracking(nfaUnionTest1, Str("01"));
                cout << "\nTest[3] \t : \t" << backtracking(nfaUnionTest1, Str("001"));

                cout << "\nTest[4] \t : \t" << backtracking(nfaUnionTest2, Str("0"));
                cout << "\nTest[5] \t : \t" << backtracking(nfaUnionTest2, Str("00"));
                cout << "\nTest[6] \t : \t" << backtracking(nfaUnionTest2, Str("001"));

                cout << "\nTest[7] \t : \t" << backtracking(nfaUnionTest3, Str("bb"));
                cout << "\nTest[8] \t : \t" << backtracking(nfaUnionTest3, Str("0"));
                cout << "\nTest[9] \t : \t" << backtracking(nfaUnionTest3, Str("01"));

                cout << "\n\n----- TRUE EXPECTED -----";

                cout << "\nTest[10] \t : \t" << backtracking(nfaUnionTest1, Str("000"));
                cout << "\nTest[11] \t : \t" << backtracking(nfaUnionTest1, Str("101"));
                cout << "\nTest[12] \t : \t" << backtracking(nfaUnionTest1, Str("10011"));

                cout << "\nTest[13] \t : \t" << backtracking(nfaUnionTest2, Str("111"));
                cout << "\nTest[14] \t : \t" << backtracking(nfaUnionTest2, Str("0011"));
                cout << "\nTest[15] \t : \t" << backtracking(nfaUnionTest2, Str("11"));

                cout << "\nTest[16] \t : \t" << backtracking(nfaUnionTest3, Str("a"));
                cout << "\nTest[17] \t : \t" << backtracking(nfaUnionTest3, Str("ba"));
                cout << "\nTest[18] \t : \t" << backtracking(nfaUnionTest3, Str("010"));
            }

            {  // Task 35 - Concatenation Tests
                cout << "\n\n"
                    << divider << "TASK 34 - (CONCAT NFAs TESTING)" << divider;

                auto nfaConcatTest1 = concatNFAs(nfa1, nfa2);
                auto nfaConcatTest2 = concatNFAs(nfa1, nfa3);
                auto nfaConcatTest3 = concatNFAs(nfa4, nfa5);
                auto nfaConcatTest4 = concatNFAs(nfa1, nfa4);
                auto nfaConcatTest5 = concatNFAs(nfa4, nfa1);

                cout << "\n----- FALSE EXPECTED -----";

                cout << "\nTest[1] \t : \t" << backtracking(nfaConcatTest1, Str("00"));
                cout << "\nTest[2] \t : \t" << backtracking(nfaConcatTest1, Str("101"));

                cout << "\nTest[3] \t : \t" << backtracking(nfaConcatTest2, Str("00"));
                cout << "\nTest[4] \t : \t" << backtracking(nfaConcatTest2, Str("10"));

                cout << "\nTest[5] \t : \t" << backtracking(nfaConcatTest3, Str("0ba"));
                cout << "\nTest[6] \t : \t" << backtracking(nfaConcatTest3, Str("001baba"));

                cout << "\n\n----- TRUE EXPECTED -----";

                cout << "\nTest[7] \t : \t" << backtracking(nfaConcatTest4, Str("101ba"));
                cout << "\nTest[8] \t : \t" << backtracking(nfaConcatTest4, Str("101baba"));
                cout << "\nTest[9] \t : \t" << backtracking(nfaConcatTest4, Str("111baba"));
                cout << "\nTest[10] \t : \t" << backtracking(nfaConcatTest4, Str("000011a"));
                cout << "\nTest[11] \t : \t" << backtracking(nfaConcatTest4, Str("101a"));
                cout << "\nTest[12] \t : \t" << backtracking(nfaConcatTest4, Str("101"));

                cout << "\nTest[13] \t : \t" << backtracking(nfaConcatTest5, Str("ba101"));
                cout << "\nTest[14] \t : \t" << backtracking(nfaConcatTest5, Str("baba101"));
                cout << "\nTest[15] \t : \t" << backtracking(nfaConcatTest5, Str("baba111"));
                cout << "\nTest[16] \t : \t" << backtracking(nfaConcatTest5, Str("a000011"));
                cout << "\nTest[17] \t : \t" << backtracking(nfaConcatTest5, Str("a101"));
                cout << "\nTest[18] \t : \t" << backtracking(nfaConcatTest5, Str("aaaa101"));
                cout << endl;
            }

            {  // Task 37 - Kleene Star Tests
                cout << "\n\n" << divider << "TASK 37 - (KLEENE STAR TESTING)" << divider;

                NFA<int> kleeneNFA1 = kleeneStar(nfa1);
                cout << "\n----- kleeneNFA1 -----";
                cout << "\nTest[1] \t : \t" << backtracking(kleeneNFA1, Str("000"));
                cout << "\nTest[2] \t : \t" << backtracking(kleeneNFA1, Str("1"));
                cout << "\nTest[3] \t : \t" << backtracking(kleeneNFA1, Str("111"));
                cout << "\nTest[4] \t : \t" << backtracking(kleeneNFA1, Str("101"));
                cout << "\nTest[5] \t : \t" << backtracking(kleeneNFA1, Str("1111"));
                cout << "\nTest[6] \t : \t" << backtracking(kleeneNFA1, Str("11"));
                cout << "\nTest[7] \t : \t" << backtracking(kleeneNFA1, Str(""))  << endl;


                NFA<int> kleeneNFA2 = kleeneStar(nfa2);
                cout << "\n----- kleeneNFA2 -----";
                cout << "\nTest[1] \t : \t" << backtracking(kleeneNFA2, Str("000"));
                cout << "\nTest[2] \t : \t" << backtracking(kleeneNFA2, Str("1"));
                cout << "\nTest[3] \t : \t" << backtracking(kleeneNFA2, Str("11"));
                cout << "\nTest[4] \t : \t" << backtracking(kleeneNFA2, Str("101"));
                cout << "\nTest[5] \t : \t" << backtracking(kleeneNFA2, Str("1111"));
                cout << "\nTest[6] \t : \t" << backtracking(kleeneNFA2, Str("111")) << endl;

                NFA<int> kleeneNFA5 = kleeneStar(nfa5);
                cout << "\n----- kleeneNFA5 -----";
                cout << "\nTest[1] \t : \t" << backtracking(kleeneNFA5, Str("0"));
                cout << "\nTest[2] \t : \t" << backtracking(kleeneNFA5, Str("1"));
                cout << "\nTest[3] \t : \t" << backtracking(kleeneNFA5, Str("10"));
                cout << "\nTest[4] \t : \t" << backtracking(kleeneNFA5, Str("01"));
                cout << "\nTest[5] \t : \t" << backtracking(kleeneNFA5, Str("1010"));
                cout << "\nTest[6] \t : \t" << backtracking(kleeneNFA5, Str("101010")) << endl;

                NFA<int> kleeneNFA6 = kleeneStar(nfa6);
                cout << "\n----- kleeneNFA6 -----";
                cout << "\nTest[1] \t : \t" << backtracking(kleeneNFA6, Str("0"));
                cout << "\nTest[2] \t : \t" << backtracking(kleeneNFA6, Str("00"));
                cout << "\nTest[3] \t : \t" << backtracking(kleeneNFA6, Str("000"));
                cout << "\nTest[4] \t : \t" << backtracking(kleeneNFA6, Str("0000"));
                cout << "\nTest[5] \t : \t" << backtracking(kleeneNFA6, Str("00000"));
                cout << "\nTest[6] \t : \t" << backtracking(kleeneNFA6, Str("000000"));
                cout << "\nTest[7] \t : \t" << backtracking(kleeneNFA6, Str(""));

            }

            {  // Task 39 - Ensure Converted NFAs Work
                cout << "\n\n" << divider << "TASK 39 - (ENSURE CONVERTED NFAs WORK)" << divider;

                auto convertedNFA1 = convertNFA(nfa1, binaryAlpha);
                testNoTraceDFA(convertedNFA1, 12);

                auto convertedNFA2 = convertNFA(nfa2, binaryAlpha);
                testNoTraceDFA(convertedNFA2, 12);

                auto convertedNFA3 = convertNFA(nfa3, unaryAlpha);
                testNoTraceDFA(convertedNFA3, 12);

                auto convertedNFA4 = convertNFA(nfa4, abAlpha);
                testNoTraceDFA(convertedNFA4, 12);

              // Task 40 - Manually Converting NFAs To DFAs | Testing Equivalence
                cout << "\n\n" << divider << "TASK 40 - (MANUALLY CONVERTING NFAS -> DFAS | TESTING EQUIVALENCE)" << divider;

                DFA<int> testDFA1([](int qi) { return qi >= 1 && qi <= 6; }, binaryAlpha, 1,
                                  [](int qi, Character c) {
                                        switch (qi) {
                                            case 1: return c.getCharacterValue() == "0" ? 1 : 2;
                                            case 2: return c.getCharacterValue() == "0" ? 3 : 4;
                                            case 3: return c.getCharacterValue() == "0" ? 1 : 4;
                                            case 4: return c.getCharacterValue() == "0" ? 5 : 4;
                                            case 5: return c.getCharacterValue() == "0" ? 6 : 4;
                                            case 6: return c.getCharacterValue() == "0" ? 6 : 4;
                                            default: return 0; } },
                                  [](int qi) { return qi == 4 || qi == 5 || qi == 6; });

                DFA<int> testDFA2([](int qi) { return qi >= 1 && qi <= 8; }, binaryAlpha, 1,
                                  [](int qi, Character c) {
                                        switch (qi) {
                                            case 1: return c.getCharacterValue() == "0" ? 1 : 2;
                                            case 2: return c.getCharacterValue() == "0" ? 3 : 6;
                                            case 3: return c.getCharacterValue() == "0" ? 4 : 7;
                                            case 4: return c.getCharacterValue() == "0" ? 1 : 2;
                                            case 5: return c.getCharacterValue() == "0" ? 4 : 7;
                                            case 6: return c.getCharacterValue() == "0" ? 5 : 8;
                                            case 7: return c.getCharacterValue() == "0" ? 3 : 6;
                                            case 8: return c.getCharacterValue() == "0" ? 5 : 8;
                                            default: return 0; } },
                                  [](int qi) { return qi == 4 || qi == 5 || qi == 7 || qi == 8; });

                DFA<int> testDFA3([](int qi) { return qi >= 1 && qi <= 8; }, unaryAlpha, 1,
                                  [](int qi, Character c) {
                                        switch (qi) {
                                            case 1: return 2;
                                            case 2: return 3;
                                            case 3: return 4;
                                            case 4: return 5;
                                            case 5: return 6;
                                            case 6: return 7;
                                            case 7: return 2;
                                            default: return 0; } },
                                  [](int qi) { return qi == 1 || qi == 3 || qi == 4 || qi == 5 || qi == 7; });

                DFA<int> testDFA4([](int qi) { return qi >= 1 && qi <= 6; }, abAlpha, 1,
                               [](int qi, Character c) {
                                        switch (qi) {
                                            case 1: return c.getCharacterValue() == "a" ? 1 : 2;
                                            case 2: return c.getCharacterValue() == "a" ? 4 : 3;
                                            case 3: return c.getCharacterValue() == "a" ? 1 : 5;
                                            case 4: return c.getCharacterValue() == "a" ? 6 : 3;
                                            case 5: return 5;
                                            case 6: return c.getCharacterValue() == "a" ? 6 : 4;
                                            default: return 0; } },
                               [](int qi) { return qi == 1 || qi == 6; });

                cout << "\nTest [1]  \t :\t" << isEqual(convertedNFA1, testDFA1);
                cout << "\nTest [2]  \t :\t" << isEqual(convertedNFA2, testDFA2);
                cout << "\nTest [3]  \t :\t" << isEqual(convertedNFA3, testDFA3);
                cout << "\nTest [4]  \t :\t" << isEqual(convertedNFA4, testDFA4);
            }

            {  // Task 43 & 44 - Write example regular expressions & example strings that would be accepted/rejected

                Regex reg1;
                Regex reg2("Epsilon");
                Regex reg3("Character", "1");
                Regex reg4("Union", vector<Regex>{Regex("Epsilon"), Regex("Character", "a")});

                Regex reg5("Circ", vector<Regex>{
                                        Regex("Union", vector<Regex>{
                                                           Regex("Character", "0"),
                                                           Regex("Character", "1")}),
                                        Regex("Star", vector<Regex>{Regex("Epsilon")})});

                Regex reg6("Star", vector<Regex>{
                                        Regex("Star", vector<Regex>{
                                                          Regex("Union", vector<Regex>{
                                                                             Regex("Epsilon"),
                                                                             Regex("Character", "1")})})});

                Regex reg7("Union", vector<Regex>{reg5, reg6});
                Regex reg8("Circ", vector<Regex>{reg6, reg7});

                cout << "\n\n" << divider << "TASK 43 - (PRINTING REGEX EXAMPLES)" << divider;
                cout << "\nTest[reg1] \t : \t" << reg1.printRegex(reg1);
                cout << "\nTest[reg2] \t : \t" << reg2.printRegex(reg2);
                cout << "\nTest[reg3] \t : \t" << reg3.printRegex(reg3);
                cout << "\nTest[reg4] \t : \t" << reg4.printRegex(reg4);
                cout << "\nTest[reg5] \t : \t" << reg5.printRegex(reg5);
                cout << "\nTest[reg6] \t : \t" << reg6.printRegex(reg6);
                cout << "\nTest[reg7] \t : \t" << reg7.printRegex(reg7);
                cout << "\nTest[reg8] \t : \t" << reg8.printRegex(reg8);

                cout << "\n\n" << divider << "TASK 44 - (EXAMPLE STRINGS THAT WOULD BE ACCEPTED OR REJECTED)" << divider;
                cout << "\n-Reg Expr- \t : \tString \t : \tAcc/Rej" << endl;
                cout << "\nTest[reg1] \t : \t\u2205 \t : \tAccepted";
                cout << "\nTest[reg1] \t : \t\u03B5 \t : \tRejected";
                cout << "\nTest[reg1] \t : \t0 \t : \tRejected" ;
                cout << "\nTest[reg1] \t : \t1 \t : \tRejected" ;

                cout << "\n\n-Reg Expr- \t : \tString \t : \tAcc/Rej" << endl;
                cout << "\nTest[reg2] \t : \t\u2205 \t : \tRejected";
                cout << "\nTest[reg2] \t : \t\u03B5 \t : \tAccepted";
                cout << "\nTest[reg2] \t : \t0 \t : \tRejected";
                cout << "\nTest[reg2] \t : \t1 \t : \tRejected";

                cout << "\n\n-Reg Expr- \t : \tString \t : \tAcc/Rej" << endl;
                cout << "\nTest[reg3] \t : \t\u2205 \t : \tRejected";
                cout << "\nTest[reg3] \t : \t\u03B5 \t : \tRejected";
                cout << "\nTest[reg3] \t : \t0 \t : \tRejected";
                cout << "\nTest[reg3] \t : \t1 \t : \tAccepted";

                cout << "\n\n-Reg Expr- \t : \tString \t : \tAcc/Rej" << endl;
                cout << "\nTest[reg4] \t : \t\u2205 \t : \tRejected";
                cout << "\nTest[reg4] \t : \t\u03B5 \t : \tAccepted";
                cout << "\nTest[reg4] \t : \t0 \t : \tRejected";
                cout << "\nTest[reg4] \t : \ta \t : \tAccepted";

                cout << "\n\n-Reg Expr- \t : \tString \t : \tAcc/Rej" << endl;
                cout << "\nTest[reg5] \t : \t\u2205 \t : \tRejected";
                cout << "\nTest[reg5] \t : \t\u03B5 \t : \tRejected";
                cout << "\nTest[reg5] \t : \t0 \t : \tRejected";
                cout << "\nTest[reg5] \t : \t1 \t : \tRejected";
                cout << "\nTest[reg5] \t : \t0\u03B5 \t : \tAccepted";
                cout << "\nTest[reg5] \t : \t0\u03B5\u03B5 \t : \tAccepted";


                cout << "\n\n" << divider << "TASK 45 - (GENERATE FUNCITON TESTS)" << divider;
                cout << "\nTest[reg1] \t : \t" << reg1.generate();
                cout << "\nTest[reg2] \t : \t" << reg2.generate();
                cout << "\nTest[reg3] \t : \t" << reg3.generate();
                cout << "\nTest[reg4] \t : \t" << reg4.generate();
                cout << "\nTest[reg5] \t : \t" << reg5.generate();
                cout << "\nTest[reg6] \t : \t" << reg6.generate();
                cout << "\nTest[reg7] \t : \t" << reg7.generate();
                cout << "\nTest[reg8] \t : \t" << reg8.generate();
            }
        }
    }
}

int main() {
    runTestCases();
    cout << endl << endl;
}
