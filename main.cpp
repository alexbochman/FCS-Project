
#include <iostream>
#include "Alphabet.hpp"
#include "DFA.hpp"

using namespace std;

int main()
{
    Alphabet alphabet;
    for(int i = 0; i < 16; i++)
    {
        cout << "Lexi(" << i << "): ";
        alphabet.lexi(i).printString();
        cout << endl;
    }

    State myState;
}