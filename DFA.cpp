
#include "DFA.hpp"

DFA::DFA() {}
DFA::DFA(Str input) : input(input) {}
DFA::DFA(Alphabet alphabet, Str input) : alphabet(alphabet), input(input) {}
DFA::~DFA() {}
bool DFA::isAccepted() { return currentState.getAcceptStatus(); }
void DFA::setCurrentState(State s) { this->currentState = s; }
void DFA::setStartState(State s) { this->startState = s; }
void DFA::setInput(Str str) { this->input = str; }

void DFA::runDFA()
{
    bool proceed = false;
    for (auto x : statesVector)
        if (x.getAcceptStatus() == true)
            proceed = true;

    while (proceed && !(input.isEmpty()))
    {
        int i = 0;
        bool moved = false;
        bool broke = false;
        std::string strValue = input.popFront();
        int transVectSize = currentState.getTransitionsVector().size() - 1;

        if (!currentState.getTransitionsVector().empty())
        {
            while (!moved)
            {
                if (currentState.getTransValueFromTuple(i) == strValue)
                {
                    currentState = statesVector.at(currentState.getIDfromTuple(i));
                    moved = true;
                }
                else if (currentState.getTransitionsVector().size() > 1 && (i != transVectSize))
                    i++;
                else
                {
                    broke = true;
                    break;
                }
            }
            if (broke) break;
        }
    }
    if (currentState.getAcceptStatus())
        std::cout << "\t[ACCEPTED]";
    else
        std::cout << "\t[REJECTED]";
    std::cout << "\t" << currentState.getAcceptStatus() << std::endl;
}

void DFA::testDFA(int testNumber)
{
    switch (testNumber)
    {
    case 1: // accepts no strings - TASK 5
    {
        State stateQ1(false, 0);
        startState = stateQ1;
        currentState = startState;
        runDFA();
        break;
    }
    case 2: // accepts only the empty string. - TASK 6
    {
        State stateQ1(true, 0);
        State stateQ2(false, 1);
        stateQ1.insertTransition(1, alphabet.getAlphabetVector().at(0));
        stateQ1.insertTransition(1, alphabet.getAlphabetVector().at(1));

        insertStatesVector(stateQ1);
        insertStatesVector(stateQ2);

        startState = stateQ1;
        currentState = startState;
        runDFA();
        break;
    }
    case 3: // only accept if string ends in a 1
    {
        State stateQ1(false, 0);
        stateQ1.insertTransition(0, alphabet.getAlphabetVector().at(0));
        stateQ1.insertTransition(1, alphabet.getAlphabetVector().at(1));

        State stateQ2(true, 1);
        stateQ2.insertTransition(1, alphabet.getAlphabetVector().at(1));
        stateQ2.insertTransition(0, alphabet.getAlphabetVector().at(0));

        insertStatesVector(stateQ1);
        insertStatesVector(stateQ2);

        startState = stateQ1;
        currentState = startState;
        runDFA();
        break;
    }
    case 4: // only accept if string ends in a 0
    {
        State stateQ0(true, 0);
        stateQ0.insertTransition(0, alphabet.getAlphabetVector().at(0));
        stateQ0.insertTransition(1, alphabet.getAlphabetVector().at(1));

        State stateQ1(false, 1);
        stateQ1.insertTransition(1, alphabet.getAlphabetVector().at(1));
        stateQ1.insertTransition(0, alphabet.getAlphabetVector().at(0));

        insertStatesVector(stateQ0);
        insertStatesVector(stateQ1);

        startState = stateQ0;
        currentState = startState;
        runDFA();
        break;
    }
    case 5: // Book figure 1.14
    {
        State stateQ0(true, 0);
        stateQ0.insertTransition(0, alphabet.getAlphabetVector().at(0));
        stateQ0.insertTransition(0, alphabet.getAlphabetVector().at(1));
        stateQ0.insertTransition(1, alphabet.getAlphabetVector().at(2));
        stateQ0.insertTransition(2, alphabet.getAlphabetVector().at(3));

        State stateQ1(false, 1);
        stateQ1.insertTransition(0, alphabet.getAlphabetVector().at(0));
        stateQ1.insertTransition(0, alphabet.getAlphabetVector().at(3));
        stateQ1.insertTransition(1, alphabet.getAlphabetVector().at(1));
        stateQ1.insertTransition(2, alphabet.getAlphabetVector().at(2));

        State stateQ2(false, 2);
        stateQ2.insertTransition(0, alphabet.getAlphabetVector().at(0));
        stateQ2.insertTransition(0, alphabet.getAlphabetVector().at(2));
        stateQ2.insertTransition(1, alphabet.getAlphabetVector().at(3));
        stateQ2.insertTransition(2, alphabet.getAlphabetVector().at(1));

        insertStatesVector(stateQ0);
        insertStatesVector(stateQ1);
        insertStatesVector(stateQ2);

        startState = stateQ0;
        currentState = startState;
        runDFA();
        break;
    }
    case 6: // Accepted only if HELLO is a substring of the input string
    {
        State stateQ0(false, 0);
        State stateQ1(false, 1);
        State stateQ2(false, 2);
        State stateQ3(false, 3);
        State stateQ4(false, 4);
        State stateQ5(true, 5);

        stateQ0.insertTransition(1, alphabet.getAlphabetVector().at(0)); // h
        stateQ1.insertTransition(2, alphabet.getAlphabetVector().at(1)); // e
        stateQ2.insertTransition(3, alphabet.getAlphabetVector().at(2)); // l
        stateQ3.insertTransition(4, alphabet.getAlphabetVector().at(2)); // l
        stateQ4.insertTransition(5, alphabet.getAlphabetVector().at(3)); // o

        stateQ0.insertTransition(0, alphabet.getAlphabetVector().at(1));
        stateQ0.insertTransition(0, alphabet.getAlphabetVector().at(2));
        stateQ0.insertTransition(0, alphabet.getAlphabetVector().at(3));
        stateQ1.insertTransition(0, alphabet.getAlphabetVector().at(0));
        stateQ2.insertTransition(0, alphabet.getAlphabetVector().at(0));
        stateQ3.insertTransition(0, alphabet.getAlphabetVector().at(0));
        stateQ4.insertTransition(0, alphabet.getAlphabetVector().at(0));

        stateQ5.insertTransition(5, alphabet.getAlphabetVector().at(0));
        stateQ5.insertTransition(5, alphabet.getAlphabetVector().at(1));
        stateQ5.insertTransition(5, alphabet.getAlphabetVector().at(2));
        stateQ5.insertTransition(5, alphabet.getAlphabetVector().at(3));

        insertStatesVector(stateQ0);
        insertStatesVector(stateQ1);
        insertStatesVector(stateQ2);
        insertStatesVector(stateQ3);
        insertStatesVector(stateQ4);
        insertStatesVector(stateQ5);

        startState = stateQ0;
        currentState = startState;
        runDFA();
        break;
    }
    case 8: // Book figure 1.12
    {
        State stateS(false, 0);
        State stateQ1(true, 1);
        State stateR1(true, 2);
        State stateQ2(false, 3);
        State stateR2(false, 4);
        stateS.insertTransition(1, alphabet.getAlphabetVector().at(0));
        stateS.insertTransition(2, alphabet.getAlphabetVector().at(1));
        stateQ1.insertTransition(1, alphabet.getAlphabetVector().at(0));
        stateQ1.insertTransition(3, alphabet.getAlphabetVector().at(1));
        stateQ2.insertTransition(1, alphabet.getAlphabetVector().at(0));
        stateQ2.insertTransition(3, alphabet.getAlphabetVector().at(1));
        stateR1.insertTransition(2, alphabet.getAlphabetVector().at(1));
        stateR1.insertTransition(4, alphabet.getAlphabetVector().at(0));
        stateR2.insertTransition(2, alphabet.getAlphabetVector().at(1));
        stateR2.insertTransition(4, alphabet.getAlphabetVector().at(0));
        insertStatesVector(stateS);
        insertStatesVector(stateQ1);
        insertStatesVector(stateR1);
        insertStatesVector(stateQ2);
        insertStatesVector(stateR2);

        startState = stateS;
        currentState = startState;
        runDFA();
        break;
    }
    case 9: // Accepts only strings of even length
    {
        State stateQ0(true, 0);
        State stateQ1(false, 1);

        stateQ0.insertTransition(1, alphabet.getAlphabetVector().at(0));
        stateQ0.insertTransition(1, alphabet.getAlphabetVector().at(1));
        stateQ1.insertTransition(0, alphabet.getAlphabetVector().at(0));
        stateQ1.insertTransition(0, alphabet.getAlphabetVector().at(1));

        insertStatesVector(stateQ0);
        insertStatesVector(stateQ1);

        startState = stateQ0;
        currentState = startState;
        runDFA();
        break;
    }
    case 10: // Modeled after an OS diagram WITH SINK STATE
    {
        State ready(true, 0);
        State running(false, 1);
        State blocked(false, 2);
        State sink(false, 3);

        ready.insertTransition(1, alphabet.getAlphabetVector().at(0));
        ready.insertTransition(3, alphabet.getAlphabetVector().at(1));
        ready.insertTransition(3, alphabet.getAlphabetVector().at(2));
        ready.insertTransition(3, alphabet.getAlphabetVector().at(3));

        running.insertTransition(0, alphabet.getAlphabetVector().at(1));
        running.insertTransition(2, alphabet.getAlphabetVector().at(2));
        running.insertTransition(3, alphabet.getAlphabetVector().at(0));
        running.insertTransition(3, alphabet.getAlphabetVector().at(3));

        blocked.insertTransition(0, alphabet.getAlphabetVector().at(3));
        blocked.insertTransition(3, alphabet.getAlphabetVector().at(0));
        blocked.insertTransition(3, alphabet.getAlphabetVector().at(1));
        blocked.insertTransition(3, alphabet.getAlphabetVector().at(2));

        insertStatesVector(ready);
        insertStatesVector(running);
        insertStatesVector(blocked);
        insertStatesVector(sink);

        startState = ready;
        currentState = startState;
        runDFA();
        break;
    }
    case 11: // Book figure 1.20 accepts all strings that contain an odd number of 1s
    {
        State stateQ0(false, 0);
        State stateQ1(true, 1);

        stateQ0.insertTransition(0, alphabet.getAlphabetVector().at(0));
        stateQ0.insertTransition(1, alphabet.getAlphabetVector().at(1));
        stateQ1.insertTransition(1, alphabet.getAlphabetVector().at(0));
        stateQ1.insertTransition(0, alphabet.getAlphabetVector().at(1));

        insertStatesVector(stateQ0);
        insertStatesVector(stateQ1);

        startState = stateQ0;
        currentState = startState;
        runDFA();
        break;
    }
    case 12: // Only accepts multiples of 3 (in binary)
    {
        State stateQ0(true, 0);
        State stateQ1(false, 1);
        State stateQ2(false, 2);

        stateQ0.insertTransition(0, alphabet.getAlphabetVector().at(0));
        stateQ0.insertTransition(1, alphabet.getAlphabetVector().at(1));

        stateQ1.insertTransition(0, alphabet.getAlphabetVector().at(1));
        stateQ1.insertTransition(2, alphabet.getAlphabetVector().at(0));

        stateQ2.insertTransition(2, alphabet.getAlphabetVector().at(1));
        stateQ2.insertTransition(1, alphabet.getAlphabetVector().at(0));

        insertStatesVector(stateQ0);
        insertStatesVector(stateQ1);
        insertStatesVector(stateQ2);

        startState = stateQ0;
        currentState = startState;
        runDFA();
        break;
    }
    default:
        std::cout << "\t[SWITCH ERROR]" << std::endl;
        break;
    }
}

DFA DFA::task7(Character c)
{
    Alphabet alphabet;
    DFA temp;
    temp.alphabet = alphabet;
    alphabet.insert(c);
    State stateQ0(false, 0);
    State stateQ1(true, 1);
    State stateQ2(false, 2);
    stateQ0.insertTransition(1, c);
    stateQ1.insertTransition(2, c);
    stateQ2.insertTransition(2, c);
    temp.insertStatesVector(stateQ0);
    temp.insertStatesVector(stateQ1);
    temp.insertStatesVector(stateQ2);
    temp.startState = stateQ0;
    temp.currentState = startState;
    return temp;
}

// DEBUGGING...
//std::cout << "\tcurrentState.getID: " << currentState.getStateID() << "  ";
// std::cout << "\t\tstrValue = " << strValue << std::endl;
// std::cout << "\t\tcurrentState.getID: " << currentState.getStateID() << std::endl;
// std::cout << "\t\tcurrentState.gettransvaluefromtuple(" << i << ") = " << currentState.getTransValueFromTuple(i) << std::endl << std::endl;