
#include "DFA.hpp"

DFA::DFA() {}
DFA::DFA(Str input) : input(input) {}
DFA::DFA(Alphabet a) : alphabet(a) {}
DFA::DFA(Alphabet alphabet, Str input) : alphabet(alphabet), input(input) {}
DFA::~DFA() {}
Str DFA::getInput() { return input; }
State DFA::getCurrentState() { return currentState; }
void DFA::setAlphabet(Alphabet alphabet) { this->alphabet = alphabet; }
void DFA::setCurrentState(State s) { this->currentState = s; }
void DFA::setStartState(State s) { this->startState = s; }
void DFA::setInput(Str str) { this->input = str; }

void DFA::printTrace()
{
    for(int i = 0; i < (signed)traceVector.size(); i++)
    {
        if (i == (signed)traceVector.size() - 1)
            std::cout << "q" << traceVector.at(i);
        else
            std::cout << "q" << traceVector.at(i) << " -> ";
    }
    traceVector.clear(); // careful here
}

std::vector<int> DFA::getTrace(Str input)
{
    this->input = input;
    runDFA();
    return traceVector;
}

void DFA::runDFA()
{
    bool proceed = false;
    for (auto x : statesVector)
        if (x.getAcceptStatus() == true)
            proceed = true;

    traceVector.push_back(currentState.getStateID());
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
                    traceVector.push_back(currentState.getStateID());
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
}

void DFA::initDFA(int testNumber)
{
    switch (testNumber)
    {
    case 1: // accepts no strings - TASK 5
    {
        State stateQ0(false, 0);
        startState = stateQ0;
        currentState = startState;
        statesVector = {stateQ0};
        break;
    }
    case 2: // accepts only the empty string. - TASK 6
    {
        State stateQ0(true, 0);
        stateQ0.insertTransition(1, alphabet.getCharacter(0));
        stateQ0.insertTransition(1, alphabet.getCharacter(1));
        State stateQ1(false, 1);
        stateQ1.insertTransition(1, alphabet.getCharacter(0));
        stateQ1.insertTransition(1, alphabet.getCharacter(1));

        statesVector = {stateQ0, stateQ1};
        startState = stateQ0;
        currentState = startState;
        break;
    }
    case 3: // only accept if string ends in a 1
    {
        State stateQ0(false, 0);
        stateQ0.insertTransition(0, alphabet.getCharacter(0));
        stateQ0.insertTransition(1, alphabet.getCharacter(1));
        State stateQ1(true, 1);
        stateQ1.insertTransition(1, alphabet.getCharacter(1));
        stateQ1.insertTransition(0, alphabet.getCharacter(0));

        statesVector = {stateQ0, stateQ1};
        startState = stateQ0;
        currentState = startState;
        break;
    }
    case 4: // only accept if string ends in a 0
    {
        State stateQ0(true, 0);
        stateQ0.insertTransition(0, alphabet.getCharacter(0));
        stateQ0.insertTransition(1, alphabet.getCharacter(1));
        State stateQ1(false, 1);
        stateQ1.insertTransition(1, alphabet.getCharacter(1));
        stateQ1.insertTransition(0, alphabet.getCharacter(0));

        statesVector = {stateQ0, stateQ1};
        startState = stateQ0;
        currentState = startState;
        break;
    }
    case 5: // Book figure 1.14
    {
        State stateQ0(true, 0);
        stateQ0.insertTransition(0, alphabet.getCharacter(0));
        stateQ0.insertTransition(0, alphabet.getCharacter(1));
        stateQ0.insertTransition(1, alphabet.getCharacter(2));
        stateQ0.insertTransition(2, alphabet.getCharacter(3));
        State stateQ1(false, 1);
        stateQ1.insertTransition(0, alphabet.getCharacter(0));
        stateQ1.insertTransition(0, alphabet.getCharacter(3));
        stateQ1.insertTransition(1, alphabet.getCharacter(1));
        stateQ1.insertTransition(2, alphabet.getCharacter(2));
        State stateQ2(false, 2);
        stateQ2.insertTransition(0, alphabet.getCharacter(0));
        stateQ2.insertTransition(0, alphabet.getCharacter(2));
        stateQ2.insertTransition(1, alphabet.getCharacter(3));
        stateQ2.insertTransition(2, alphabet.getCharacter(1));

        statesVector = {stateQ0, stateQ1, stateQ2};
        startState = stateQ0;
        currentState = startState;
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
        stateQ0.insertTransition(1, alphabet.getCharacter(0)); // h
        stateQ1.insertTransition(2, alphabet.getCharacter(1)); // e
        stateQ2.insertTransition(3, alphabet.getCharacter(2)); // l
        stateQ3.insertTransition(4, alphabet.getCharacter(2)); // l
        stateQ4.insertTransition(5, alphabet.getCharacter(3)); // o
        stateQ0.insertTransition(0, alphabet.getCharacter(1));
        stateQ0.insertTransition(0, alphabet.getCharacter(2));
        stateQ0.insertTransition(0, alphabet.getCharacter(3));
        stateQ1.insertTransition(0, alphabet.getCharacter(0));
        stateQ2.insertTransition(0, alphabet.getCharacter(0));
        stateQ3.insertTransition(0, alphabet.getCharacter(0));
        stateQ4.insertTransition(0, alphabet.getCharacter(0));
        stateQ5.insertTransition(5, alphabet.getCharacter(0));
        stateQ5.insertTransition(5, alphabet.getCharacter(1));
        stateQ5.insertTransition(5, alphabet.getCharacter(2));
        stateQ5.insertTransition(5, alphabet.getCharacter(3));

        statesVector = {stateQ0, stateQ1, stateQ2, stateQ3, stateQ4, stateQ5};
        startState = stateQ0;
        currentState = startState;
        break;
    }
    case 8: // Book figure 1.12
    {
        State stateS(false, 0);
        stateS.insertTransition(1, alphabet.getCharacter(0));
        stateS.insertTransition(2, alphabet.getCharacter(1));
        State stateQ1(true, 1);
        stateQ1.insertTransition(1, alphabet.getCharacter(0));
        stateQ1.insertTransition(3, alphabet.getCharacter(1));
        State stateR1(true, 2);
        stateR1.insertTransition(2, alphabet.getCharacter(1));
        stateR1.insertTransition(4, alphabet.getCharacter(0));
        State stateQ2(false, 3);
        stateQ2.insertTransition(1, alphabet.getCharacter(0));
        stateQ2.insertTransition(3, alphabet.getCharacter(1));
        State stateR2(false, 4);
        stateR2.insertTransition(2, alphabet.getCharacter(1));
        stateR2.insertTransition(4, alphabet.getCharacter(0));

        statesVector = {stateS, stateQ1, stateR1, stateQ2, stateR2};
        startState = stateS;
        currentState = startState;
        break;
    }
    case 9: // Accepts only strings of even length
    {
        State stateQ0(true, 0);
        stateQ0.insertTransition(1, alphabet.getCharacter(0));
        stateQ0.insertTransition(1, alphabet.getCharacter(1));
        State stateQ1(false, 1);
        stateQ1.insertTransition(0, alphabet.getCharacter(0));
        stateQ1.insertTransition(0, alphabet.getCharacter(1));

        statesVector = {stateQ0, stateQ1};
        startState = stateQ0;
        currentState = startState;
        break;
    }
    case 10: // Modeled after an OS diagram WITH SINK STATE
    {
        State ready(true, 0);
        ready.insertTransition(1, alphabet.getCharacter(0));
        ready.insertTransition(3, alphabet.getCharacter(1));
        ready.insertTransition(3, alphabet.getCharacter(2));
        ready.insertTransition(3, alphabet.getCharacter(3));
        State running(false, 1);
        running.insertTransition(0, alphabet.getCharacter(1));
        running.insertTransition(2, alphabet.getCharacter(2));
        running.insertTransition(3, alphabet.getCharacter(0));
        running.insertTransition(3, alphabet.getCharacter(3));
        State blocked(false, 2);
        blocked.insertTransition(0, alphabet.getCharacter(3));
        blocked.insertTransition(3, alphabet.getCharacter(0));
        blocked.insertTransition(3, alphabet.getCharacter(1));
        blocked.insertTransition(3, alphabet.getCharacter(2));
        State sink(false, 3);

        statesVector = {ready, running, blocked, sink};
        startState = ready;
        currentState = startState;
        break;
    }
    case 11: // Book figure 1.20 accepts all strings that contain an odd number of 1s
    {
        State stateQ0(false, 0);
        stateQ0.insertTransition(0, alphabet.getCharacter(0));
        stateQ0.insertTransition(1, alphabet.getCharacter(1));
        State stateQ1(true, 1);
        stateQ1.insertTransition(1, alphabet.getCharacter(0));
        stateQ1.insertTransition(0, alphabet.getCharacter(1));

        statesVector = {stateQ0, stateQ1};
        startState = stateQ0;
        currentState = startState;
        break;
    }
    case 12: // Only accepts multiples of 3 (in binary)
    {
        State stateQ0(true, 0);
        stateQ0.insertTransition(0, alphabet.getCharacter(0));
        stateQ0.insertTransition(1, alphabet.getCharacter(1));
        State stateQ1(false, 1);
        stateQ1.insertTransition(0, alphabet.getCharacter(1));
        stateQ1.insertTransition(2, alphabet.getCharacter(0));
        State stateQ2(false, 2);
        stateQ2.insertTransition(2, alphabet.getCharacter(1));
        stateQ2.insertTransition(1, alphabet.getCharacter(0));

        statesVector = {stateQ0, stateQ1, stateQ2};
        startState = stateQ0;
        currentState = startState;
        break;
    }
    default:
        std::cout << "\t[INIT DFA ERROR]" << std::endl;
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

    statesVector = {stateQ0, stateQ1, stateQ2};
    temp.startState = stateQ0;
    temp.currentState = startState;
    return temp;
}

// DEBUGGING...
// std::cout << "\t\tstrValue = " << strValue << std::endl;
// std::cout << "\t\tcurrentState.getID: " << currentState.getStateID() << std::endl;
// std::cout << "\t\tcurrentState.gettransvaluefromtuple(" << i << ") = " << currentState.getTransValueFromTuple(i) << std::endl << std::endl;