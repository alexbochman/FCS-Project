
#include <iostream>
#include "Alphabet.hpp"
#include "DFA.hpp"

using namespace std;

int main()
{
    // DFA test cases
    {
        {
            cout << "\n[1] REJECT ALL STRINGS";
            Alphabet alphabet;
            alphabet.insert(Character("0"));
            alphabet.insert(Character("1"));
            for (int i = 0; i < 10; i++)
            {
                if (!(i % 10))
                    cout << endl;
                cout << "Lexi(" << i << "): ";
                alphabet.lexi(i).printString();
                Str input = alphabet.lexi(i);
                DFA myMachine(alphabet, input);
                myMachine.testDFA(1);
            }
            cout << "====================================\n\n";
        }

        {
            cout << "[2] ACCEPT ONLY EMPTY STRING";
            Alphabet alphabet;
            alphabet.insert(Character("0"));
            alphabet.insert(Character("1"));
            for (int i = 0; i < 10; i++)
            {
                if (!(i % 10))
                    cout << endl;
                cout << "Lexi(" << i << "): ";
                alphabet.lexi(i).printString();
                Str input = alphabet.lexi(i);
                DFA myMachine(alphabet, input);
                myMachine.testDFA(2);
            }
            cout << "====================================\n\n";
        }

        {
            cout << "[3] ACCEPT ONLY IF STRING ENDS WITH 1";
            Alphabet alphabet;
            alphabet.insert(Character("0"));
            alphabet.insert(Character("1"));
            for (int i = 0; i < 10; i++)
            {
                if (!(i % 10))
                    cout << endl;
                cout << "Lexi(" << i << "): ";
                alphabet.lexi(i).printString();
                Str input = alphabet.lexi(i);
                DFA myMachine(alphabet, input);
                myMachine.testDFA(3);
            }
            cout << "====================================\n\n";
        }

        {
            cout << "[4] ACCEPT ONLY IF STRING ENDS WITH 0";
            Alphabet alphabet;
            alphabet.insert(Character("0"));
            alphabet.insert(Character("1"));
            for (int i = 0; i < 10; i++)
            {
                if (!(i % 10))
                    cout << endl;
                cout << "Lexi(" << i << "): ";
                alphabet.lexi(i).printString();
                Str input = alphabet.lexi(i);
                DFA myMachine(alphabet, input);
                myMachine.testDFA(4);
            }
            cout << "====================================\n\n";
        }

        {
            cout << "[5] BOOK EXAMPLE FIGURE 1.14";
            Alphabet alphabet;
            alphabet.insert(Character("R"));
            alphabet.insert(Character("0"));
            alphabet.insert(Character("1"));
            alphabet.insert(Character("2"));
            for (int i = 0; i < 10; i++)
            {
                if (!(i % 10))
                    cout << endl;
                cout << "Lexi(" << i << "): ";
                alphabet.lexi(i).printString();
                Str input = alphabet.lexi(i);
                DFA myMachine(alphabet, input);
                myMachine.testDFA(5);
            }
            cout << "====================================\n\n";
        }

        {
            cout << "[6] ACCEPT ONLY IF \"HELLO\" IS A SUBSTRING";
            Alphabet alphabet;
            alphabet.insert(Character("H"));
            alphabet.insert(Character("E"));
            alphabet.insert(Character("L"));
            alphabet.insert(Character("O"));
            for (int i = 0; i < 10; i++)
            {
                if (!(i % 10))
                    cout << endl;
                cout << "Lexi(" << i << "): ";
                alphabet.lexi(i).printString();
                Str input = alphabet.lexi(i);
                DFA myMachine(alphabet, input);
                myMachine.testDFA(6);
            }
            cout << "====================================\n\n";
        }

        {
            cout << "[7] TASK 7 - Function returns DFA that only accepts single input character";
            Alphabet alphabet;
            Character test("0 ");
            alphabet.insert(test);
            DFA myMachine = myMachine.task7(test);

                for (int i = 0; i < 10; i++)
                {
                    if (!(i % 10))
                        cout << endl;
                    cout << "Lexi(" << i << "): ";
                    alphabet.lexi(i).printString();
                    Str input = alphabet.lexi(i);
                    myMachine.setInput(input);
                    myMachine.runDFA();
                }
            cout << "====================================\n\n";
        }

        {
            cout << "[8] BOOK FIGURE 1.12";
            Alphabet alphabet;
            alphabet.insert(Character("a"));
            alphabet.insert(Character("b"));

            for (int i = 0; i < 10; i++)
            {
                if (!(i % 10))
                    cout << endl;
                cout << "Lexi(" << i << "): ";
                alphabet.lexi(i).printString();
                Str input = alphabet.lexi(i);
                DFA myMachine(alphabet, input);
                myMachine.testDFA(8);
            }
            cout << "====================================\n\n";
        }

        {
            cout << "[9] ACCEPTS ONLY STRINGS OF EVEN LENGTH";
            Alphabet alphabet;
            alphabet.insert(Character("a"));
            alphabet.insert(Character("b"));

            for (int i = 0; i < 10; i++)
            {
                if (!(i % 10))
                    cout << endl;
                cout << "Lexi(" << i << "): ";
                alphabet.lexi(i).printString();
                Str input = alphabet.lexi(i);
                DFA myMachine(alphabet, input);
                myMachine.testDFA(9);
            }
            cout << "====================================\n\n";
        }

        {
            cout << "[10] OS DIAGRAM WITH SINK STATE";
            Alphabet alphabet;
            alphabet.insert(Character("<Run> "));
            alphabet.insert(Character("<OS Schedule> "));
            alphabet.insert(Character("<Request Resource> "));
            alphabet.insert(Character("<Release Resource> "));

            for (int i = 0; i < 10; i++)
            {
                if (!(i % 10))
                    cout << endl;
                cout << "Lexi(" << i << "): ";
                alphabet.lexi(i).printString();
                Str input = alphabet.lexi(i);
                DFA myMachine(alphabet, input);
                cout << "\t";
                myMachine.testDFA(10);
            }
            cout << "====================================\n\n";
        }

        {
            cout << "[11] BOOK FIGURE 1.20 ACCEPTS ALL STRINGS THAT CONTAIN AN ODD NUMBER OF 1s";
            Alphabet alphabet;
            alphabet.insert(Character("0"));
            alphabet.insert(Character("1"));

            for (int i = 0; i < 10; i++)
            {
                if (!(i % 10))
                    cout << endl;
                cout << "Lexi(" << i << "): ";
                alphabet.lexi(i).printString();
                Str input = alphabet.lexi(i);
                DFA myMachine(alphabet, input);
                myMachine.testDFA(11);
            }
            cout << "====================================\n\n";
        }

        {
            cout << "[12] ONLY ACCEPTS MULTIPLES OF 3s (IN BINARY)";
            Alphabet alphabet;
            alphabet.insert(Character("0"));
            alphabet.insert(Character("1"));

            for (int i = 0; i < 20; i++)
            {
                if (!(i % 10))
                    cout << endl;
                cout << "Lexi(" << i << "): ";
                alphabet.lexi(i).printString();
                Str input = alphabet.lexi(i);
                DFA myMachine(alphabet, input);
                myMachine.testDFA(12);
            }
            cout << "====================================\n\n";
        }
    }

}