/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 2 - Creature Types: Inheritance
*/

#include "Dragon.hpp"

/**
    Default constructor.
    Default-initializes all private members. 
    Default Category: MYSTICAL
    Default element: NONE
    Default number of head(s): 1
    Booleans are default-initialized to False. 
*/
Dragon::Dragon(): Creature("NAMELESS", MYSTICAL), affinity_{NONE}, num_heads_{1}, can_fly_{false} {}

/**
    Parameterized constructor.
    @param      : The name of the Dragon (a reference to string)
    @param      : The category of the Dragon (a Category enum) with default value MYSTICAL
    @param      : The Dragon's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : The Dragon's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : A flag indicating whether the Dragon is tame, with default value False
    @param      : The element (an Element enum), with default value NONE if not provided
    @param      : The number of heads (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : A flag indicating whether the Dragon can fly, with default value False
    @post       : The private members are set to the values of the corresponding parameters.
    Hint: Notice the default arguments in the parameterized constructor.
*/
Dragon::Dragon(const std::string& name, Category category, int hitpoints, int level, bool tame, Element affinity, int num_heads, bool can_fly)
        : Creature(name, category, hitpoints, level, tame), affinity_{affinity}, num_heads_{num_heads}, can_fly_{can_fly} {
            if(!setNumberOfHeads(num_heads)){
                num_heads_ = 1;
            }
        }

/**
    Getter for the element.
    @return     : The element (a string representation of the Element enum)
*/
std::string Dragon::getElement() const {
    switch (affinity_) {
        case Element::NONE:
            return "NONE";
        case Element::FIRE:
            return "FIRE";
        case Element::WATER:
            return "WATER";
        case Element::EARTH:
            return "EARTH";
        case Element::AIR:
            return "AIR";
        default:
            return "UNKNOWN";
    }
}

/**
    Setter for the element.
    @param      : A reference to the element (an Element enum)
    @post       : The element is set to the value of the parameter.
*/
void Dragon::setElement(const Element& affinity) {
    affinity_ = affinity;
}

/**
    Getter for the number of heads.
    @return     : The number of heads (an integer)
*/
int Dragon::getNumberOfHeads() const {
    return num_heads_;
}

/**
    Setter for the number of heads.
    @param      : A reference to the number of heads (an integer)
    @pre        : The number of heads is > 0. Do nothing for invalid values.
    @post       : The number of heads is set to the value of the parameter.
    @return     : True if the number of heads is set, false otherwise.
*/
bool Dragon::setNumberOfHeads(const int& num_heads) {
    if (num_heads > 0) {
        num_heads_ = num_heads;
        return true;
    }
    return false;
}

/**
    Getter for the flight flag.
    @return     : The flight flag (a boolean)
*/
bool Dragon::getFlight() const {
    return can_fly_;
}

/**
    Setter for the flight flag.
    @param      : A reference to the flight flag (a boolean)
    @post       : The flight flag is set to the value of the parameter.
*/
void Dragon::setFlight(const bool& can_fly) {
    can_fly_ = can_fly;
}