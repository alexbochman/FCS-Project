
#include <iostream>
#include "Alphabet.hpp"
#include "DFA.hpp"

using namespace std;

int main()
{
    Alphabet alphabet;
    for(int i = 0; i < 256; i++)
    {
        if(!(i % 10)) cout << endl;
        cout << "Lexi(" << i << "): ";
        alphabet.lexi(i).printString();
        cout << endl;
    }

    State myState(Character("ab666"));
    cout << "\nmyState.getStateValue(): = " << myState.getStateValue() << endl;
}