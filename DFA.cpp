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

DFA::DFA(Alphabet alphabet, Str input) : alphabet(alphabet), input(input) {}

DFA::~DFA() {}

void DFA::runDFA()
{
    bool proceed = false;
    for (auto x : statesVector)
        if (x.getAcceptStatus() == true)
            proceed = true;

    // Outside Loop:
    // bool proceed makes sure there's at least one accepting state &&
    // while the input string isn't empty, pop off the first value to be used as a driver for determining transitions.
    while (proceed && !(input.isEmpty()))
    {
        std::string strValue = input.popFront();
        int i = 0;
        bool moved = false;
        int comparator = currentState.getTransitionsVector().size() - 1;
        bool broke = false;
        // Inside Loop:
        // While the currentState hasn't moved, iterate through the currentState's
        // possible transitions (transition vector) and compare the currentState's transitionValue with
        // the current popped value. If equal, move the currentState, set flag to true.
        if (!currentState.getTransitionsVector().empty())
        {
            while (!moved)
            {
                if (currentState.getTransValueFromTuple(i) == strValue)
                {
                    currentState = statesVector.at(currentState.getIDfromTuple(i));
                    moved = true;
                }
                else if (currentState.getTransitionsVector().size() > 1 && (i != comparator))
                {
                    // std::cout << "\t\tstrValue = " << strValue << std::endl;
                    // std::cout << "\t\tcurrentState.getID: " << currentState.getStateID() << std::endl;
                    // std::cout << "\t\tcurrentState.gettransvaluefromtuple(" << i << ") = " << currentState.getTransValueFromTuple(i) << std::endl << std::endl;
                    i++;
                }
                else
                {
                    broke = true;
                    break;
                }
            }
            if (broke) break;
        }
    }

    //std::cout << "\tcurrentState.getID: " << currentState.getStateID() << "  ";

    if (currentState.getAcceptStatus())
        std::cout << "\t[ACCEPTED]";
    else
        std::cout << "\t[REJECTED]";
    std::cout << "\t" << currentState.getAcceptStatus() << std::endl;
}

bool DFA::isAccepted() { return currentState.getAcceptStatus(); }

void DFA::generateDFA(int testNumber) // Don't forget to include the generateDFA in main.
{
    switch(testNumber)
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
    case 6: // HELO
    {

        // State stateQ0(false, 0);
        // stateQ0.insertTransition(1, alphabet.getAlphabetVector().at(0));
        // // I think I need to build in logic that accounts for what happens when
        // // we don't find the transition we're looking for.
        // // Additionally, logic for only having 1 possible transition??
        // State stateQ1(true, 1);
        // stateQ1.insertTransition(1, alphabet.getAlphabetVector().at(0));

        State stateQ0(false, 0);
        stateQ0.insertTransition(1, alphabet.getAlphabetVector().at(0)); // h

        State stateQ1(false, 1);
        stateQ1.insertTransition(2, alphabet.getAlphabetVector().at(1)); // e

        State stateQ2(false, 2);
        stateQ2.insertTransition(3, alphabet.getAlphabetVector().at(2)); // l

        State stateQ3(false, 3);
        stateQ3.insertTransition(3, alphabet.getAlphabetVector().at(2)); // l
        stateQ3.insertTransition(4, alphabet.getAlphabetVector().at(3)); // o

        State stateQ4(true, 4);
        stateQ4.insertTransition(4, alphabet.getAlphabetVector().at(3)); // o

        insertStatesVector(stateQ0);
        insertStatesVector(stateQ1);
        insertStatesVector(stateQ2);
        insertStatesVector(stateQ3);
        insertStatesVector(stateQ4);

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



















// Below I'm trying to modify generateDFA to accept parameters that define:
// the number of states, the initilization of each state, and all of the
// transition rules by using a 4-tuple

/*
// tuple (accepting? from? to? value?)
void DFA::generateDFA(int numStates, int startIndex, std::vector<std::tuple<bool, int, int, std::string>> rules)

for (int i = 0; i < numStates; i++)
{
    State tempState(std::get<0>(rules.at(i)), i);
    for (int j = 0; j < (signed)rules.size(); j++)
        if (i == std::get<1>(rules.at(j)))
            tempState.insertTransition(std::get<2>(rules.at(i)), std::get<3>(rules.at(j)));
    insertStatesVector(tempState);
}
startState = statesVector.at(startIndex);
*/