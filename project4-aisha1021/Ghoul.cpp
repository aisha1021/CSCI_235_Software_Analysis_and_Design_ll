/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 4 - The MycoMorsel
*/

#include "Ghoul.hpp"

/**
    Default constructor.
    Default-initializes all private members. 
    Default Category: UNDEAD
    Default decay: 0
    Default faction: NONE
    Booleans are default-initialized to False. 
*/
Ghoul::Ghoul() :  decay_{0}, faction_{NONE}, transformation_{false} {
    setCategory(UNDEAD); 
}

/**
    Parameterized constructor.
    @param      : The name of the Ghoul (a reference string)
    @param      : The category of the Ghoul (a Category enum) with default value UNDEAD
    @param      : The Ghoul's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : The Ghoul's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : A flag indicating whether the Ghoul is tame, with default value False
    @param      : The level of decay (an integer), with default value 0 if not provided, or if the value provided is negative
    @param      : The faction (a Faction enum), with default value NONE if not provided
    @param      : A flag indicating whether the Ghoul can transform, with default value False
    @post       : The private members are set to the values of the corresponding parameters.
    Hint: Notice the default arguments in the parameterized constructor.
*/
Ghoul::Ghoul(const std::string& name, Category category, int hitpoints, int level, bool tame, int decay, Faction faction, bool transformation) : Creature(name, category, hitpoints, level, tame) {
    if(!setDecay(decay)) {
        decay_ = 0;
    }
    faction_ = faction;
    transformation_ = transformation;
}

/**
    Getter for the level of decay.
    @return     : The level of decay (an integer)
*/
int Ghoul::getDecay() const {
    return decay_;
}

/**
    Setter for the level of decay.
    @param      : A reference to the level of decay (an integer)
    @pre        : The level of decay must be >= 0 (do nothing otherwise)
    @post       : The level of decay is set to the value of the parameter.
    @return     : true if the level of decay was set, false otherwise
*/
bool Ghoul::setDecay(const int& decay) {
    if(decay >= 0) {
        decay_ = decay;
        return true;
    } else {
        return false;
    }
}

/**
    Getter for the faction.
    @return     : The faction (a string representation of the Faction enum)
*/
std::string Ghoul::getFaction() const {
    switch(faction_) {
        case FLESHGORGER:
            return "FLESHGORGER";
        case SHADOWSTALKER:
            return "SHADOWSTALKER";
        case PLAGUEWEAVER:
            return "PLAGUEWEAVER";
        default:
            return "NONE";
    }
}

/**
    Setter for the faction.
    @param      : A reference to the faction (a Faction enum)
    @post       : The faction is set to the value of the parameter.
*/
void Ghoul::setFaction(const Faction& faction) {
    faction_ = faction;
}

/**
    Getter for the transformation.
    @return     : The transformation (a boolean)
*/
bool Ghoul::getTransformation() const {
    return transformation_;
}

/**
    Setter for the transformation.
    @param      : A reference to the transformation (a boolean)
    @post       : The transformation is set to the value of the parameter.
*/
void Ghoul::setTransformation(const bool& transformation) {
    transformation_ = transformation;
}

/**
    @post     : displays Ghoul data in the form:
    GHOUL - [NAME]\n
    CATEGORY: [CATEGORY]\n
    HP: [HITPOINTS]\n
    LVL: [LEVEL]\n
    TAME: [TRUE/FALSE]\n
    DECAY: [DECAY]\n
    FACTION: [FACTION]\n
    IT [CAN/CANNOT] TRANSFORM\n"
    
    Example:
    GHOUL - JHRAT
    CATEGORY: MYSTICAL
    HP: 4
    LVL: 8
    TAME: TRUE
    DECAY: 3
    FACTION: FLESHGORGER
    IT CAN TRANSFORM
    
*/
void Ghoul::display() const {
    std::cout << "GHOUL - " << getName() << std::endl; // Displaying Ghoul's name
    std::cout << "CATEGORY: " << getCategory() << std::endl; // Displaying Ghoul's category
    std::cout << "HP: " << getHitpoints() << std::endl; // Displaying Ghoul's hitpoints
    std::cout << "LVL: " << getLevel() << std::endl; // Displaying Ghoul's level
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl; // Displaying whether Ghoul is tame or not
    std::cout << "DECAY: " << decay_ << std::endl; // Displaying Ghoul's decay
    std::cout << "FACTION: " << getFaction() << std::endl; // Displaying Ghoul's faction
    std::cout << "IT " << (transformation_ ? "CAN" : "CANNOT") << " TRANSFORM" << std::endl; // Displaying whether Ghoul can transform or not
}


/**
    @post   : If the creature is UNDEAD, it becomes tame if not already, as it appreciates the gesture, even though as an UNDEAD it does not really eat. It gains 1 hitpoint from the mysterious powers it receives by wearing the mushroom as a hat. Nothing else happens.
              If the creature is of Faction FLESHGORGER, it becomes so offended by being offered a mushroom that it becomes untamed if it was tame. If it was already untamed, it leaves the Cavern. Nothing else happens.
              If the creature was of Faction SHADOWSTALKER, if it was untame, it hides from the mushroom and nothing happens. If it was tame, it eats the mushroom and loses 1 hitpoint, unless it only had 1 hitpoint left in which case it stays at 1 hitpoint but becomes untame. Nothing else happens.
    @return   : true if the creature leaves the Cavern, false otherwise
*/
bool Ghoul::eatMycoMorsel() {
    // If Ghoul is undead
    if (getCategory() == "UNDEAD") {
        // If Ghoul is not tame, make it tame
        if (!isTame()) {
            setTame(true); // Make Ghoul tame
        }
        setHitpoints(getHitpoints() + 1); // Increase Ghoul's hitpoints by 1
    } 
    // If Ghoul belongs to faction FLESHGORGER
    else if (getFaction() == "FLESHGORGER") {
        // If Ghoul is tame, make it untame
        if (isTame()) {
            setTame(false); // Make Ghoul untame
        } 
        // If Ghoul is untame, return true to indicate leaving cavern
        else {
            return true; // Ghoul leaves cavern
        }
    } 
    // If Ghoul belongs to faction SHADOWSTALKER
    else if (getFaction() == "SHADOWSTALKER") {
        // If Ghoul is tame
        if (isTame()) {
            // If Ghoul has more than 1 hitpoint, decrease hitpoints by 1
            if (getHitpoints() > 1) {
                setHitpoints(getHitpoints() - 1); // Decrease Ghoul's hitpoints by 1
            } 
            // If Ghoul has only 1 hitpoint, make it untame
            else {
                setTame(false); // Make Ghoul untame
            }
        }
    }
    return false; // Default case: Ghoul does not leave cavern
}
