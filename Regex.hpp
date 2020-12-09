
#include <string.h>
#include <vector>
#include <random>

#include "Alphabet.hpp"

// Task 41 - Define Regex data type
class Regex
{
public:
    Regex() : type("Empty") {};
    Regex(std::string type) : type("Epsilon") {};
    Regex(std::string type, std::string c) : type("Character"), c(c) {};
    Regex(std::string type, std::vector<Regex> regVect) : type(type), regVect(regVect) {};
    ~Regex() {};

    std::string type;
    Character c;
    std::vector<Regex> regVect;

    // Task 42 - Write the Regex printer function
    std::string printRegex(Regex current) {
        if (current.type == "Empty")
            return "\u2205";
        else if (current.type == "Epsilon")
            return "\u03B5";
        else if(current.type == "Character")
            return current.c.getCharacterValue();
        else if(current.type == "Union") {
            std::string lhs = printRegex(current.regVect.at(0));
            std::string rhs = printRegex(current.regVect.at(1));
            return "(" + lhs + " U " + rhs + ")";
        } else if(current.type == "Star")
            return "(" + printRegex(current.regVect.at(0)) + ")*";
        else {
            std::string lhs = printRegex(current.regVect.at(0));
            std::string rhs = printRegex(current.regVect.at(1));
            return "(" + lhs + " \u25CB " + rhs + ")";
        }
    }

    // Task 45 - (Generator) Write a function that accepts a regular expression and generates a random string that would be accepted by it.
    std::string generate() {
        std::string output;

        std::random_device rd;   //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd());  //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1, 2);

        if(type == "Empty")
            return "\u2205";
        else if (type == "Epsilon")
            return "\u03B5";
        else if (type == "Character")
            return c.getCharacterValue();
        else if(type == "Star")

            do { output += c.getCharacterValue();
            } while(distrib(gen) % 2 == 1);

        else if (type == "Union") {
            if (distrib(gen) % 2 == 0)
                return regVect[0].generate();
            else
                return regVect[1].generate();
        }
        else if(type == "Circ")
            output = regVect[0].generate() + regVect[1].generate();

        return output;
    }
};
