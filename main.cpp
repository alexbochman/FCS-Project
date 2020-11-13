
#include <algorithm>
#include <iostream>
#include <iterator>
#include <optional>
#include <utility>

#include "Alphabet.hpp"
#include "DFA.hpp"
#include "NFA.hpp"

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
Str searchAlgo(DFA<T> m, T qi, std::vector<T> *visited, Str output) {
    vector<Character> E = m.getAlpha().getAlphabetVector();
    if (m.accepts(output))
        return output;

    for (int i = 0; i < (int)E.size(); i++) {
        auto qNext = m.getTransitions()(qi, E.at(i));
        auto it = std::find(visited->begin(), visited->end(), qNext);
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
    auto fPrime = [=](T qi) { return !F(qi); };
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

    return DFA<std::pair<F, G>>([Q1, Q2](std::pair<F, G> state) { return Q1(state.first) && Q2(state.second); },
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

// Task 24 - Convert DFA to NFA
template <typename T>
NFA<T> convertDFA(DFA<T> m) {
    auto dPrime = [=](T state, Character c) { return c.getCharacterValue().empty() ? vector<T>{} : vector<T>{m.d(state, c)}; };
    return NFA<T>(m.Q, m.E, m.q0, dPrime, m.F);
}

// Task 27 - (Oracle) determines if the trace is a valid execution of the NFA and accepts results in the given boolean.
template <typename T>
bool oracle(NFA<T> m, vector<pair<T, string>> trace) {
    if (trace.size() == 0) return true;

    for (unsigned int i = 1; i < trace.size(); i++) {
        auto currentState = trace[i - 1].first;
        auto nextState = trace[i].first;
        string currentString = trace[i - 1].second;
        string nextString = trace[i].second;
        Character c(popFront(currentString));

        if (trace[i - 1].second == nextString) {
            auto vect1 = m.d(currentState, Character(""));
            if (find(vect1.begin(), vect1.end(), nextState) == vect1.end())
                return false;

        } else if (currentString != nextString)
            return false;

        auto vect = m.d(currentState, Character(c));
        if (find(vect.begin(), vect.end(), nextState) == vect.end())
            return false;
    }
    return true;
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

        cout << "\n\n"
             << divider << "TASK 20 & 21 - EQUALITY TESTS" << divider;
        cout << "\nisEqual(endsIn1, evenLength)\t\t  :\t" << isEqual(endsIn1, evenLength);
        cout << "\nisEqual(bookFigure120, bookFigure112)\t  :\t" << isEqual(bookFigure120, bookFigure112);
        cout << "\nisEqual(noString, emptyString)\t\t  :\t" << isEqual(noString, emptyString);
        cout << "\nisEqual(noString, evenLength)\t\t  :\t" << isEqual(noString, evenLength);
        cout << endl;
        cout << "\nisEqual(endsIn1, endsIn1)\t\t  :\t" << isEqual(endsIn1, endsIn1);
        cout << "\nisEqual(noString, noString)\t\t  :\t" << isEqual(noString, noString);
        cout << "\nisEqual(emptyString, emptyString)\t  :\t" << isEqual(emptyString, emptyString);
        cout << "\nisEqual(alexDFA, alexDFA)\t\t  :\t" << isEqual(alexDFA, alexDFA);

        cout << "\n\n"
             << divider << "TASK 22 - VERIFYING UNION, INTERSECT, COMPLEMENT" << divider;
        cout << "\nTest [1]  \t :\t" << isEqual(unionDFAs(emptyString, complementDFA(emptyString)), complementDFA(noString));
        cout << "\nTest [2]  \t :\t" << isEqual(unionDFAs(noString, emptyString), intersectDFAs(complementDFA(noString), emptyString));
        cout << "\nTest [3]  \t :\t" << isEqual(intersectDFAs(emptyString, complementDFA(emptyString)), noString);
        cout << "\nTest [4]  \t :\t" << isEqual(intersectDFAs(complementDFA(noString), alexDFA), alexDFA);

        auto emptyNFA = convertDFA(emptyString);
    }

    {  // Task 25 - Write example NFAs. NFAs Initialized Below, Test Calls At The Bottom
        // NFA 1 through 4 correspond to FCS book figures 1.27, 1.31, 1.34, and 1.36 respectively
        NFA<int> nfa1([](int qi) { return qi == 1 || qi == 2 || qi == 3 || qi == 4; }, binaryAlpha, 1,
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
                                  possibleTrans.push_back(3);
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

        NFA<int> nfa2([](int qi) { return qi == 1 || qi == 2 || qi == 3 || qi == 4; }, binaryAlpha, 1,
                      [](int qi, Character c) {
                          vector<int> possibleTrans;
                          if (c.getCharacterValue().empty()) return possibleTrans;

                          switch (qi) {
                              case 1:
                                  possibleTrans.push_back(1);
                                  if (c.getCharacterValue() == "1") possibleTrans.push_back(2);
                                  break;
                              case 2:
                                  possibleTrans.push_back(3);
                                  break;
                              case 3:
                                  possibleTrans.push_back(4);
                                  break;
                          }
                          return possibleTrans;
                      },
                      [](int qi) { return qi == 4; });

        NFA<int> nfa3([](int qi) { return qi >= 1 || qi <= 6; }, unaryAlpha, 1,
                      [](int qi, Character c) {
                          vector<int> possibleTrans;

                          switch (qi) {
                              case 1:
                                  possibleTrans.push_back(2);
                                  possibleTrans.push_back(3);
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
                      [](int qi) { return qi == 4; });

        NFA<int> nfa4([](int qi) { return qi == 1 || qi == 2 || qi == 3; }, abAlpha, 1,
                      [](int qi, Character c) {
                          vector<int> possibleTrans;
                          switch (qi) {
                              case 1:
                                  possibleTrans.push_back(3);
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
        NFA<int> nfa5([](int qi) { return qi == 1 || qi == 2 || qi == 3 || qi == 4 || qi == 5; }, binaryAlpha, 1,
                      [](int qi, Character c) {
                          vector<int> possibleTrans;

                          if (c.getCharacterValue().empty())
                              return possibleTrans;

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
                                  possibleTrans.push_back(5);
                                  break;
                          }
                          return possibleTrans;
                      },
                      [](int qi) { return qi == 4; });

        {  // Task 26 - For each example NFA, write a dozen traces of their behavior.
            cout << "\n\n"
                 << divider << "TASK 26 - FOR EACH EXAMPLE NFA, WRITE TRACES OF THEIR BEHAVIOR" << divider;
            vector<pair<int, string>> traceVectorNfa1_1{
                pair<int, string>(1, "101"),
                pair<int, string>(2, "01"),
                pair<int, string>(3, "1"),
                pair<int, string>(4, "")};

            vector<pair<int, string>> traceVectorNfa1_2{
                pair<int, string>(1, "00111"),
                pair<int, string>(1, "0111"),
                pair<int, string>(1, "111"),
                pair<int, string>(2, "11"),
                pair<int, string>(3, "11"),
                pair<int, string>(4, "1"),
                pair<int, string>(4, "")};

            vector<pair<int, string>> traceVectorNfa1_3{
                pair<int, string>(1, "11"),
                pair<int, string>(2, "1"),
                pair<int, string>(3, "1"),
                pair<int, string>(4, "")};

            cout << "\n\nnfaTrace1_1 oracle: " << oracle(nfa1, traceVectorNfa1_1) << endl;
            cout << "nfaTrace1_2 oracle: " << oracle(nfa1, traceVectorNfa1_2) << endl;
            cout << "nfaTrace1_3 oracle: " << oracle(nfa1, traceVectorNfa1_3) << endl;

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

            cout << "\nnfaTrace2_1 oracle: " << oracle(nfa2, traceVectorNfa2_1) << endl;
            cout << "nfaTrace2_2 oracle: " << oracle(nfa2, traceVectorNfa2_2) << endl;

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

            cout << "\nnfaTrace3_1 oracle: " << oracle(nfa3, traceVectorNfa3_1) << endl;
            cout << "nfaTrace3_2 oracle: " << oracle(nfa3, traceVectorNfa3_2) << endl;

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

            cout << "\nnfaTrace4_1 oracle: " << oracle(nfa4, traceVectorNfa4_1) << endl;
            cout << "nfaTrace4_2 oracle: " << oracle(nfa4, traceVectorNfa4_2) << endl;

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

            cout << "\nnfaTrace5_1 oracle: " << oracle(nfa5, traceVectorNfa5_1) << endl;
            cout << "nfaTrace5_2 oracle: " << oracle(nfa5, traceVectorNfa5_2) << endl;
        }
    }
}

int main() {
    runTestCases();
    cout << endl;
}
