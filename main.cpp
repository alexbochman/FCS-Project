
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
    {
        cout << "\n[1] REJECT ALL STRINGS";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA myMachine(a);
        myMachine.initDFA(1);

        for (int i = 0; i < 20; i++)
        {
            if (!(i % 10)) cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[2] ACCEPT ONLY EMPTY STRING";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA myMachine(a);
        myMachine.initDFA(2);

        for (int i = 0; i < 20; i++)
        {
            if (!(i % 10))cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[3] ACCEPT ONLY IF STRING ENDS WITH 1";

        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA myMachine(a);
        myMachine.initDFA(3);

        for (int i = 0; i < 20; i++)
        {
            if (!(i % 10))cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[4] ACCEPT ONLY IF STRING ENDS WITH 0";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA myMachine(a);
        myMachine.initDFA(4);

        for (int i = 0; i < 20; i++)
        {
            if (!(i % 10))
                cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[5] BOOK EXAMPLE FIGURE 1.14";
        Alphabet a;
        a.insert(Character("R"));
        a.insert(Character("0"));
        a.insert(Character("1"));
        a.insert(Character("2"));
        DFA myMachine(a);
        myMachine.initDFA(5);

        for (int i = 0; i < 20; i++)
        {
            if (!(i % 10))
                cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[6] ACCEPT ONLY IF \"HELLO\" IS A SUBSTRING";
        Alphabet a;
        a.insert(Character("H"));
        a.insert(Character("E"));
        a.insert(Character("L"));
        a.insert(Character("O"));
        DFA myMachine(a);
        myMachine.initDFA(6);

        for (int i = 0; i < 20; i++)
        {
            if (!(i % 10))
                cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[7] TASK 7 - Function returns DFA that only accepts single input character";
        Alphabet alphabet;
        Character character("X ");
        alphabet.insert(character);

        DFA myMachine = myMachine.task7(character);

        for (int i = 0; i < 4; i++)
        {
            if (!(i % 10))
                cout << endl;
            cout << "Lexi(" << i << "): ";
            alphabet.lexi(i).printString();
            Str input = alphabet.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[8] BOOK FIGURE 1.12";
        Alphabet a;
        a.insert(Character("a"));
        a.insert(Character("b"));
        DFA myMachine(a);
        myMachine.initDFA(8);

        for (int i = 0; i < 20; i++)
        {
            if (!(i % 10))
                cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[9] ACCEPTS ONLY STRINGS OF EVEN LENGTH";
        Alphabet a;
        a.insert(Character("a"));
        a.insert(Character("b"));
        DFA myMachine(a);
        myMachine.initDFA(9);

        for (int i = 0; i < 20; i++)
        {
            if (!(i % 10))
                cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[10] OS DIAGRAM WITH SINK STATE";
        Alphabet a;
        a.insert(Character("<Run> "));
        a.insert(Character("<OS Schedule> "));
        a.insert(Character("<Request Resource> "));
        a.insert(Character("<Release Resource> "));
        DFA myMachine(a);
        myMachine.initDFA(10);

        for (int i = 0; i < 20; i++)
        {
            if (!(i % 10))
                cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[11] BOOK FIGURE 1.20 ACCEPTS ALL STRINGS THAT CONTAIN AN ODD NUMBER OF 1s";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA myMachine(a);
        myMachine.initDFA(11);

        for (int i = 0; i < 20; i++)
        {
            if (!(i % 10))
                cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[12] ONLY ACCEPTS MULTIPLES OF 3s (IN BINARY)";
        Alphabet a;
        a.insert(Character("0"));
        a.insert(Character("1"));
        DFA myMachine(a);
        myMachine.initDFA(12);

        for (int i = 0; i < 20; i++)
        {
            if (!(i % 10))
                cout << endl;
            cout << "Lexi(" << i << "): ";
            a.lexi(i).printString();
            Str input = a.lexi(i);
            isStrAccepted(myMachine, input);
            cout << " " << endl;
        }
        cout << "====================================\n\n";
    }
}

int main()
{
    runDfaTestCases();
}
