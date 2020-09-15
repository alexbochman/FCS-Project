#include "DFA.hpp"

State::State() {}
State::State(bool acceptStatus, int stateID) : acceptStatus(acceptStatus), stateID(stateID) {}
State::~State() {}

// Function creates a tuple with the state and its transition value and
// inserts the tuple into a vector. As in: GO TO [stateID] WITH VALUE OF [transitionValue]
void State::insertTransition(int stateID, Character transitionValue)
{
    std::tuple<int, Character> transition;
    transition = std::make_tuple(stateID, transitionValue);
    transitions.push_back(transition);
}

DFA::DFA() {}
DFA::DFA(Alphabet alphabet, Str input) : alphabet(alphabet), input(input) {}
DFA::~DFA() {}

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

bool DFA::isAccepted() { return currentState.getAcceptStatus(); }

void DFA::generateDFA(int testNumber)
{
    switch (testNumber)
    {
    case 1: // accepts no strings
    {
        State stateQ1(false, 0);
        startState = stateQ1;
        currentState = startState;
        runDFA();
        break;
    }
    case 2:
        // accepts only the empty string.
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
    case 5: // from the book
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
    case 6: // Accepted only if HELLO is anywhere in string
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
    case 7:
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
    case 8:
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
    case 9:
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
    case 10:
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
    case 11:
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
    case 12:
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
    default:
        std::cout << "\t[SWITCH ERROR]" << std::endl;
        break;
    }
}


void DFA::test()
{

}



// DEBUGGING...

//std::cout << "\tcurrentState.getID: " << currentState.getStateID() << "  ";
// std::cout << "\t\tstrValue = " << strValue << std::endl;
// std::cout << "\t\tcurrentState.getID: " << currentState.getStateID() << std::endl;
// std::cout << "\t\tcurrentState.gettransvaluefromtuple(" << i << ") = " << currentState.getTransValueFromTuple(i) << std::endl << std::endl;