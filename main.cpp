
#include <iostream>
#include "Alphabet.hpp"
#include "DFA.hpp"

using namespace std;

int main()
{
    {
        cout << "[1]=================================";
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
            myMachine.generateDFA(1);
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[2]=================================";
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
            myMachine.generateDFA(2);
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[3]=================================";
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
            myMachine.generateDFA(3);
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[4]=================================";
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
            myMachine.generateDFA(4);
        }
        cout << "====================================\n\n";
    }

    {
        cout << "[5]=================================";
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
            myMachine.generateDFA(5);
        }
        cout << "====================================\n\n";
    }
    {
        cout << "[6]=================================";
        Alphabet alphabet;
        alphabet.insert(Character("H"));
        alphabet.insert(Character("E"));
        alphabet.insert(Character("L"));
        alphabet.insert(Character("O"));
        alphabet.printVector(alphabet.getAlphabetVector());
        for (int i = 0; i < 449; i++)
        {
            if (!(i % 10))
                cout << endl;
            cout << "Lexi(" << i << "): ";
            alphabet.lexi(i).printString();
            Str input = alphabet.lexi(i);
            DFA myMachine(alphabet, input);
            myMachine.generateDFA(6);
        }
        cout << "====================================\n\n";
    }
}