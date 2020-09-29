
#include <iostream>
#include "Alphabet.hpp"
#include "DFA.hpp"

using namespace std;

// Task 10 - Write a function that given a DFA and a string, determines if the string is accepted.
bool isStrAccepted(DFA m, Str input)
{
    m.setInput(input);
    m.runDFA();

    if (m.getCurrentState().getAcceptStatus())
        std::cout << "\t[ACCEPTED]\t";
    else
        std::cout << "\t[REJECTED]\t";

    m.printTrace();
    return m.getCurrentState().getAcceptStatus() ? true : false;
}

// Task 8, 9 - Write a dozen example DFAs and test their behavior
void runDfaTestCases()
{
    auto tester = [=](DFA myMachine, Alphabet a){
        for (int i = 0; i < 20; i++){
            if (!(i % 10)) cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
    };

    { // [1] REJECT ALL STRINGS
        cout << "\n[1] REJECT ALL STRINGS";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA myMachine(a);
        myMachine.initDFA(1);
        tester(myMachine, a);
        cout << "====================================\n\n";
    }

    { // [2] ACCEPT ONLY EMPTY STRING
        cout << "[2] ACCEPT ONLY EMPTY STRING";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA myMachine(a);
        myMachine.initDFA(2);
        tester(myMachine, a);
        cout << "====================================\n\n";
    }

    { // [3] ACCEPT ONLY IF STRING ENDS WITH 1
        cout << "[3] ACCEPT ONLY IF STRING ENDS WITH 1";

        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA myMachine(a);
        myMachine.initDFA(3);
        tester(myMachine, a);
        cout << "====================================\n\n";
    }

    { // [4] ACCEPT ONLY IF STRING ENDS WITH 0
        cout << "[4] ACCEPT ONLY IF STRING ENDS WITH 0";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA myMachine(a);
        myMachine.initDFA(4);
        tester(myMachine, a);
        cout << "====================================\n\n";
    }

    { // [5] BOOK EXAMPLE FIGURE 1.14
        cout << "[5] BOOK EXAMPLE FIGURE 1.14";
        Alphabet a;
        a.insert(Character("R"));
        a.insert(Character("0"));
        a.insert(Character("1"));
        a.insert(Character("2"));
        DFA myMachine(a);
        myMachine.initDFA(5);
        tester(myMachine, a);
        cout << "====================================\n\n";
    }

    { // [6] ACCEPT ONLY IF \"HELLO\" IS A SUBSTRING
        cout << "[6] ACCEPT ONLY IF \"HELLO\" IS A SUBSTRING";
        Alphabet a;
        a.insert(Character("H"));
        a.insert(Character("E"));
        a.insert(Character("L"));
        a.insert(Character("O"));
        DFA myMachine(a);
        myMachine.initDFA(6);
        tester(myMachine, a);
        cout << "====================================\n\n";
    }

    { // [7] TASK 7 - Function returns DFA that only accepts single input character
        cout << "[7] TASK 7 - Function returns DFA that only accepts single input character";
        Alphabet a;
        Character character("X ");
        a.insert(character);
        DFA myMachine = myMachine.task7(character);
        tester(myMachine, a);
        cout << "====================================\n\n";
    }

    { // [8] BOOK FIGURE 1.12
        cout << "[8] BOOK FIGURE 1.12";
        Alphabet a;
        a.insert(Character("a"));
        a.insert(Character("b"));
        DFA myMachine(a);
        myMachine.initDFA(8);
        tester(myMachine, a);
        cout << "====================================\n\n";
    }

    { // [9] ACCEPTS ONLY STRINGS OF EVEN LENGTH
        cout << "[9] ACCEPTS ONLY STRINGS OF EVEN LENGTH";
        Alphabet a;
        a.insert(Character("a"));
        a.insert(Character("b"));
        DFA myMachine(a);
        myMachine.initDFA(9);
        tester(myMachine, a);
        cout << "====================================\n\n";
    }

    { // [10] OS DIAGRAM WITH SINK STATE
        cout << "[10] OS DIAGRAM WITH SINK STATE";
        Alphabet a;
        a.insert(Character("<Run> "));
        a.insert(Character("<OS Schedule> "));
        a.insert(Character("<Request Resource> "));
        a.insert(Character("<Release Resource> "));
        DFA myMachine(a);
        myMachine.initDFA(10);
        tester(myMachine, a);
        cout << "====================================\n\n";
    }

    { // [11] BOOK FIGURE 1.20 ACCEPTS ALL STRINGS THAT CONTAIN AN ODD NUMBER OF 1s
        cout << "[11] BOOK FIGURE 1.20 ACCEPTS ALL STRINGS THAT CONTAIN AN ODD NUMBER OF 1s";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA myMachine(a);
        myMachine.initDFA(11);
        tester(myMachine, a);
        cout << "====================================\n\n";
    }

    { // [12] ONLY ACCEPTS MULTIPLES OF 3s (IN BINARY)
        cout << "[12] ONLY ACCEPTS MULTIPLES OF 3s (IN BINARY)";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA myMachine(a);
        myMachine.initDFA(12);
        tester(myMachine, a);
        cout << "====================================\n\n";
    }
}

int main()
{
    runDfaTestCases();
}
