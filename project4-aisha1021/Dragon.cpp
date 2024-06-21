/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 4 - The MycoMorsel
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
Dragon::Dragon() : element_{NONE}, number_of_heads_{1}, flight_{false} {
    setCategory(MYSTICAL);  
}

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
Dragon::Dragon(const std::string& name, Category category, int hitpoints, int level, bool tame, Element element, int number_of_heads, bool flight) : Creature(name, category, hitpoints, level, tame) {
    element_ = element;
    if(!setNumberOfHeads(number_of_heads))
    {
        number_of_heads_ = 1;
    }
    flight_ = flight;
}

/**
    Getter for the element.
    @return     : The element (a string representation of the Element enum)
*/
std::string Dragon::getElement() const {
    switch(element_)
    {
        case FIRE:
            return "FIRE";
        case WATER:
            return "WATER";
        case EARTH:
            return "EARTH";
        case AIR:
            return "AIR";
        default:
            return "NONE";
    }
}

/**
    Setter for the element.
    @param      : A reference to the element (an Element enum)
    @post       : The element is set to the value of the parameter.
*/
void Dragon::setElement(const Element& element) {
    element_ = element;
}

/**
    Getter for the number of heads.
    @return     : The number of heads (an integer)
*/
int Dragon::getNumberOfHeads() const {
    return number_of_heads_;
}

/**
    Setter for the number of heads.
    @param      : A reference to the number of heads (an integer)
    @pre        : The number of heads is > 0. Do nothing for invalid values.
    @post       : The number of heads is set to the value of the parameter.
    @return     : True if the number of heads is set, false otherwise.
*/
bool Dragon::setNumberOfHeads(const int& number_of_heads) {
    if(number_of_heads > 0) {
        number_of_heads_ = number_of_heads;
        return true;
    } else {
        return false;
    }
}

/**
    Getter for the flight_ flag.
    @return     : The flight_ flag (a boolean)
*/
bool Dragon::getFlight() const {
    return flight_;
}

/**
    Setter for the flight_ flag.
    @param      : A reference to the flight flag (a boolean)
    @post       : The flight_ flag is set to the value of the parameter.
*/
void Dragon::setFlight(const bool& flight) {
    flight_ = flight;
}

/**
    @post     : displays Dragon data in the form:
    "DRAGON - [NAME]\n
    CATEGORY: [CATEGORY]\n
    HP: [HITPOINTS]\n
    LVL: [LEVEL]\n
    TAME: [TRUE/FALSE]\n
    ELEMENT: [ELEMENT]\n
    HEADS: [NUMBER OF HEADS]\n
    IT [CAN/CANNOT] FLY\n"
    
    Example:
    DRAGON - JHIZARD
    CATEGORY: ALIEN
    HP: 7
    LVL: 5
    TAME: TRUE
    ELEMENT: FIRE
    HEADS: 3
    IT CAN FLY
    
*/
// Function to display Dragon information
void Dragon::display() const {
    std::cout << "DRAGON - " << getName() << std::endl; // Displaying Dragon's name
    std::cout << "CATEGORY: " << getCategory() << std::endl; // Displaying Dragon's category
    std::cout << "HP: " << getHitpoints() << std::endl; // Displaying Dragon's hitpoints
    std::cout << "LVL: " << getLevel() << std::endl; // Displaying Dragon's level
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl; // Displaying if Dragon is tame or not
    std::cout << "ELEMENT: " << getElement() << std::endl; // Displaying Dragon's element
    std::cout << "HEADS: " << getNumberOfHeads() << std::endl; // Displaying Dragon's number of heads
    std::cout << "IT " << (getFlight() ? "CAN" : "CANNOT") << " FLY" << std::endl; // Displaying if Dragon can fly or not
}


/**
    @post   : If the creature is UNDEAD, it becomes tame if not already, as it appreciates the gesture, even though as an UNDEAD it does not really eat. 
              It gains 1 hitpoint from the mysterious powers it receives by wearing the mushroom as a hat. Nothing else happens.
              If the creature is an ALIEN, it consumes the mushroom and gains 1 additional hitpoint. Nothing else happens.
              If the creature is MYSTICAL, it consumes the mushroom and gains 1 additional hitpoint if it has FIRE or EARTH affinity (Either by cooking the mushroom first, or by being fungi-tolerant). Nothing else happens.
              But if it is MYSTICAL and has WATER, AIR, or no affinity, if it only has 1 hitpoint left, it doesn't want to risk it and leaves the Cavern. If it has more than 1 hitpoint, it loses 1 hitpoint and becomes untamed if it was tame. Nothing else happens.
    @return : true if the creature leaves the Cavern, false otherwise
*/
bool Dragon::eatMycoMorsel() {
    // If Dragon is undead
    if (getCategory() == "UNDEAD") {
        setTame(true); // Set Dragon as tame
        setHitpoints(getHitpoints() + 1); // Increase Dragon's hitpoints by 1
    } 
    // If Dragon is alien
    else if (getCategory() == "ALIEN") {
        setHitpoints(getHitpoints() + 1); // Increase Dragon's hitpoints by 1
    } 
    // If Dragon is mystical
    else if (getCategory() == "MYSTICAL") {
        // If Dragon's element is fire, earth, or mystical
        if (getElement() == "FIRE" || getElement() == "EARTH" || getElement() == "MYSTICAL") {
            setHitpoints(getHitpoints() + 1); // Increase Dragon's hitpoints by 1
        } 
        // If Dragon's element is not fire, earth, or mystical
        else {
            // If Dragon only has 1 hitpoint left
            if (getHitpoints() == 1) {
                return true; // Dragon cannot eat myco morsel and will leave cavern
            } 
            // If Dragon has more than 1 hitpoint left
            else {
                setHitpoints(getHitpoints() - 1); // Decrease Dragon's hitpoints by 1
                setTame(false); // Set Dragon as untamed
            }
        }
    }
    return false; // Default case: Dragon does not leave cavern
}

