
#include <iostream>
#include <optional>
#include "Alphabet.hpp"
#include "DFA.hpp"

using namespace std;


auto popFront(vector<int> vect) {
    int temp = vect.at(0);
    vect.erase(vect.begin());
    return temp;
}

// Task 7 - Write a function that returns a DFA that only accepts the given Character
DFA givenCharacterDFA(string input) {
    Alphabet E;
    E.insert(input);
    DFA m([](int qi) { return qi == 0 || qi == 1 || qi == 2; }, E, 0,
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
bool isStrAccepted(DFA m, Str w) {
    bool accepted = m.accepts(w);
    w.printString();
    if (accepted) cout << "\tAccepted\t";
    else cout << "\tRejected\t";
    m.trace();
    return accepted;
}

// Task 12 - Write a function that given a DFA, returns a string that would be accepted.
tuple<bool, Str> possibleString(DFA m)
{
    bool foundAnAcceptState = false;
    vector<Character> c;
    vector<int> visited;
    vector<int> notVisited;
    auto F = m.getAcceptingStates();

    for (int i = 0; m.getStates()(i); i++)
        notVisited.push_back(i);
    for(int i = 0; i < (signed)notVisited.size(); i++)
        if (F(i) == true)
            foundAnAcceptState = true;

    if(foundAnAcceptState) {
        visited.push_back(notVisited.at(0));
        notVisited.erase(notVisited.begin());
        while(1) {
            if(F(visited.back())) {
                for (int i = 0; i < (signed)(visited.size() - 1); i++)
                    c.push_back(m.getTransValue(i, i+1));
                return make_tuple(true, Str(c));
            }
            visited.push_back(notVisited.at(0));
            notVisited.erase(notVisited.begin());
        }
    }
    return make_tuple(false, Str(c));
}

// Task 13 - (Complement) Write a function that takes one DFA and returns a DFA that accepts what the given one doesn't (and vice versa).
DFA complementDFA(DFA m) {
    cout << "COMPLEMENT OF ABOVE DFA\n";
    auto F = m.getAcceptingStates();
    function<bool(int)> fPrime = [=](int qi) { return !F(qi); };
    return DFA(m.getStates(), m.getAlpha(), m.getStartState(), m.getTransitions(), fPrime);
}

void runDfaTestCases() {

    Alphabet binaryAlpha;
    binaryAlpha.setAlphaVector(vector<Character>{Character("0"), Character("1")});
    Alphabet abAlpha;
    abAlpha.setAlphaVector(vector<Character>{Character("a"), Character("b")});
    Alphabet alexAlpha;
    alexAlpha.setAlphaVector(vector<Character>{Character("A"), Character("L"), Character("E"), Character("X")});

    auto test = [](DFA m, int count) {
        cout << "POSSIBLE STRING : ";

        if (get<0>(possibleString(m)))
            get<1>(possibleString(m)).printString();
        else
            cout << "[NO POSSIBLE STRING]";

        cout << "\nINPUT\t       ACCEPT STATUS\tTRACE\n\n";
        Alphabet E = m.getAlpha();
        for (int i = 0; i < count; i++) {
            cout << "Lexi(" << i << "): ";
            isStrAccepted(m, E.lexi(i));
        }
        cout << "============================================\n\n";
    };

    { // [1] DFA ACCEPTS NO STRINGS (TASK 5)
        DFA noString([](int qi) { return qi == 0; }, binaryAlpha, 0,
                        [](int qi, Character c) { return 0; },
                        [](int qi) { return 0; });
        cout << "\n[1] ACCEPTS NO STRINGS\n";
        cout << "============================================\n\n";
        test(noString, 12);
        test(complementDFA(noString), 12);
    }
    { // [2] DFA ONLY ACCEPTS EMPTY STRING (TASK 6)
        DFA emptyString([](int qi) { return qi == 0 || qi == 1; }, binaryAlpha, 0,
                        [](int qi, Character c) { return 1; },
                        [](int qi) { return qi == 0; });
        cout << "\n[2] ACCEPT ONLY EMPTY STRING\n";
        cout << "============================================\n\n";
        test(emptyString, 12);
        test(complementDFA(emptyString), 12);
    }
    { // [3] FUNCTION RETURNS A DFA THAT ONLY ACCEPTS GIVEN CHARACTER (TASK 7)
        DFA task7DFA = givenCharacterDFA("X");
        cout << "\n[3] FUNCTION RETURNS A DFA THAT ONLY ACCEPTS GIVEN CHARACTER (TASK 7)\n";
        cout << "============================================\n\n";
        test(task7DFA, 5);
        test(complementDFA(task7DFA), 5);
    }
    { // [4] DFA ONLY ACCEPTS STRINGS OF EVEN LENGTH
        DFA evenLength([](int qi) { return qi == 0 || qi == 1; }, binaryAlpha, 0,
                       [](int qi, Character c) { return !qi; },
                       [](int qi) { return !qi; });
        cout << "\n[4] STRINGS OF EVEN LENGTH\n";
        cout << "============================================\n\n";
        test(evenLength, 12);
        test(complementDFA(evenLength), 12);
    }
    { // [5] DFA ONLY ACCEPTS EVEN BINARY NUMBERS
        DFA evenBinary([](int qi) { return qi == 0 || qi == 1; }, binaryAlpha, 0,
                       [](int qi, Character c) { return !(c.getCharacterValue() == "0"); },
                       [](int qi) { return qi == 0; });
        cout << "\n[5] STRINGS OF EVEN BINARY NUMBERS\n";
        cout << "============================================\n\n";
        test(evenBinary, 12);
        test(complementDFA(evenBinary), 12);
    }
    { // [6] DFA BOOK FIGURE 1.12
        DFA bookFigure([](int qi) { return qi == 0 || qi == 1 || qi == 2 || qi == 3 || qi == 4; }, abAlpha, 0,
                       [](int qi, Character c) {
                    switch (qi) {
                    case 0: return c.getCharacterValue() == "a" ? 1 : 2;
                    case 1: return c.getCharacterValue() == "a" ? 1 : 3;
                    case 2: return c.getCharacterValue() == "a" ? 4 : 2;
                    case 3: return c.getCharacterValue() == "a" ? 1 : 3;
                    case 4: return c.getCharacterValue() == "a" ? 4 : 2;
                    default: return 0; } },
                       [](int qi) { return qi == 1 || qi == 2; });
        cout << "\n[6] BOOK FIGURE 1.12\n";
        cout << "============================================\n\n";
        test(bookFigure, 12);
        test(complementDFA(bookFigure), 12);
    }
    { // [7] ONLY ACCEPT IF STRING ENDS IN A 1
        DFA endsIn1([](int qi) { return qi == 0 || qi == 1; }, binaryAlpha, 0,
                       [](int qi, Character c) { return c.getCharacterValue() == "1"; },
                       [](int qi) { return qi == 1; });
        cout << "\n[7] ONLY ACCEPT IF STRING ENDS IN A 1\n";
        cout << "============================================\n\n";
        test(endsIn1, 12);
        test(complementDFA(endsIn1), 12);
    }
    { // [8] ONLY ACCEPT IF STRING CONTAINS AN ODD NUMBER OF 1s (BOOK FIGURE 1.20)
        DFA bookFigure([](int qi) { return qi == 0 || qi == 1; }, binaryAlpha, 0,
                       [](int qi, Character c) {
                    switch (qi) {
                    case 0: return c.getCharacterValue() == "1";
                    case 1: return c.getCharacterValue() == "0";
                    default: return false; } },
                        [](int qi) { return qi == 1; });
        cout << "\n[8] ONLY ACCEPT IF STRING CONTAINS AN ODD NUMBER OF 1s (BOOK FIGURE 1.20)\n";
        cout << "============================================\n\n";
        test(bookFigure, 12);
        test(complementDFA(bookFigure), 12);
    }
    { // [9] ONLY ACCEPT IF "ALEX" IS A SUBSTRING
        DFA alexDfa([](int qi) { return qi == 0 || qi == 1 || qi == 2 || qi == 3 || qi == 4; }, alexAlpha, 0,
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
        cout << "\n[9] ONLY ACCEPT IF ""ALEX"" IS A SUBSTRING\n";
        cout << "============================================\n\n";
        test(alexDfa, 12);
        test(complementDFA(alexDfa), 12);
    }
}

int main() {
    runDfaTestCases();
    cout << endl;
}
