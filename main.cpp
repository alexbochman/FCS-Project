
#include <iostream>
#include <optional>
#include "Alphabet.hpp"
#include "DFA.hpp"

using namespace std;

// Task 12 - Write a function that given a DFA, returns a string that would be accepted.
tuple<bool, Str> possibleString(DFA m)
{
    vector<Character> c;
    vector<State> visited;
    vector<State> notVisited = m.getStatesVector();
    if(m.hasAnAcceptState())
    {
        visited.push_back(notVisited.at(0));
        notVisited.erase(notVisited.begin());
        while (1)
        {
            if (visited.back().getAcceptStatus())
            {
                for (int i = 0; i < (signed)(visited.size() - 1); i++)
                    c.push_back(visited.at(i).getTransValueGivenID(i + 1));
                return make_tuple(true, Str(c));
            }
            visited.push_back(notVisited.at(0));
            notVisited.erase(notVisited.begin());
        }
    }
    return make_tuple(false, Str(c));
}

// Task 10 - Write a function that given a DFA and a string, determines if the string is accepted.
bool isStrAccepted(DFA m, Str input)
{
    m.setInput(input);
    m.runDFA();

    if (m.getCurrentState().getAcceptStatus())
        cout << "\t[ACCEPTED]\t";
    else
        cout << "\t[REJECTED]\t";

    m.printTrace();
    return m.getCurrentState().getAcceptStatus() ? true : false;
}

void runDfaTestCases()
{
    auto tester = [](DFA m, Alphabet a) {
        cout << "\nPOSSIBLE STRING : ";
        if (get<0>(possibleString(m)))
            get<1>(possibleString(m)).printString();
        else
            cout << "False";
        cout << "\n=============================================";
        for (int i = 0; i < 10; i++)
        {
            if (!(i % 10))
                cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(m, input);
            cout << " " << endl;
        }
        cout << "=============================================\n\n";
    };

    { // [1] REJECT ALL STRINGS
        cout << "[1] REJECT ALL STRINGS";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA m(a);
        m.initDFA(1);
        tester(m, a);
    }

    { // [2] ACCEPT ONLY EMPTY STRING
        cout << "[2] ACCEPT ONLY EMPTY STRING";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA m(a);
        m.initDFA(2);
        tester(m, a);
    }

    { // [3] ACCEPT ONLY IF STRING ENDS WITH 1
        cout << "[3] ACCEPT ONLY IF STRING ENDS WITH 1";

        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA m(a);
        m.initDFA(3);
        tester(m, a);
    }

    { // [4] ACCEPT ONLY IF STRING ENDS WITH 0
        cout << "[4] ACCEPT ONLY IF STRING ENDS WITH 0";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA m(a);
        m.initDFA(4);
        tester(m, a);
    }

    { // [5] BOOK EXAMPLE FIGURE 1.14
        cout << "[5] BOOK EXAMPLE FIGURE 1.14";
        Alphabet a;
        a.insert(Character("R"));
        a.insert(Character("0"));
        a.insert(Character("1"));
        a.insert(Character("2"));
        DFA m(a);
        m.initDFA(5);
        tester(m, a);
    }

    { // [6] ACCEPT ONLY IF \"HELLO\" IS A SUBSTRING
        cout << "[6] ACCEPT ONLY IF \"HELLO\" IS A SUBSTRING";
        Alphabet a;
        a.insert(Character("H"));
        a.insert(Character("E"));
        a.insert(Character("L"));
        a.insert(Character("O"));
        DFA m(a);
        m.initDFA(6);
        tester(m, a);
    }

    { // [7] TASK 7 - Function returns DFA that only accepts single input character
        // cout << "[7] TASK 7 - Function returns DFA that only accepts single input character";
        // Alphabet a;
        // Character character("X ");
        // a.insert(character);
        // DFA m = m.task7(character);
        // tester(m, a);
    }

    { // [8] BOOK FIGURE 1.12
        cout << "[8] BOOK FIGURE 1.12";
        Alphabet a;
        a.insert(Character("a"));
        a.insert(Character("b"));
        DFA m(a);
        m.initDFA(8);
        tester(m, a);
    }

    { // [9] ACCEPTS ONLY STRINGS OF EVEN LENGTH
        cout << "[9] ACCEPTS ONLY STRINGS OF EVEN LENGTH";
        Alphabet a;
        a.insert(Character("a"));
        a.insert(Character("b"));
        DFA m(a);
        m.initDFA(9);
        tester(m, a);
    }

    { // [10] OS DIAGRAM WITH SINK STATE
        // cout << "[10] OS DIAGRAM WITH SINK STATE";
        // Alphabet a;
        // a.insert(Character("<Run> "));
        // a.insert(Character("<OS Schedule> "));
        // a.insert(Character("<Request Resource> "));
        // a.insert(Character("<Release Resource> "));
        // DFA m(a);
        // m.initDFA(10);
        // tester(m, a);
    }

    { // [11] BOOK FIGURE 1.20 ACCEPTS ALL STRINGS THAT CONTAIN AN ODD NUMBER OF 1s
        cout << "[11] BOOK FIGURE 1.20 ACCEPTS ALL STRINGS THAT CONTAIN AN ODD NUMBER OF 1s";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA m(a);
        m.initDFA(11);
        tester(m, a);
    }

    { // [12] ONLY ACCEPTS MULTIPLES OF 3s (IN BINARY)
        cout << "[12] ONLY ACCEPTS MULTIPLES OF 3s (IN BINARY)";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA m(a);
        m.initDFA(12);
        tester(m, a);
    }
}

int main()
{
    cout << endl;
    runDfaTestCases();
}
