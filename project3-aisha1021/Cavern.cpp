/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 3 - The Cavern
*/

#include "Cavern.hpp"

/**
    Default constructor.
    Default-initializes all private members. 
*/
Cavern::Cavern() : level_sum_(0), tame_count_(0) {}

/** 
    * @param   :   A reference to a Creature entering the Cavern
    * @post    :   If the given Creature is not already in the Cavern, add Creature to the Cavern and updates the level sum and the tame Creature count if the creature is tame.
    * @return  :   returns true if a Creature was successfully added to the Cavern, false otherwise
               :   Hint: Use the above definition of equality will help determine if a Creature is already in the Cavern
**/
bool Cavern::enterCavern(const Creature& creature) {
    if (!contains(creature)) {
        add(creature);

        level_sum_ += creature.getLevel();
        
        if (creature.isTame()) {
            tame_count_++;
        }
        
        return true;
    }
    
    return false;
}

/** 
    * @param   :   A  reference to a Creature leaving the Cavern
    * @return  :   returns true if a creature was successfully removed from the Cavern (i.e. items_), false otherwise
    * @post    :   removes the creature from the Cavern and updates the level sum. 
                   If the Creature is tame it also updates the tame count.
**/
bool Cavern::exitCavern(const Creature& creature) {
    if (remove(creature)) {
        level_sum_ -= creature.getLevel();
        
        if (creature.isTame()) {
            tame_count_--;
        }
        
        return true;
    }
    
    return false;
}

/** 
    * @return   :  The integer level count of all the creatures currently in the Cavern
**/
int Cavern::getLevelSum() const {
    return level_sum_;
}

/**
    * @return   :  The average level (int) of all the creatures in the Cavern
    * @post     :  Computes the average level (double) of the Cavern rounded to the NEAREST integer.
 **/
int Cavern::calculateAvgLevel() const {
    if (getCurrentSize() == 0) {
        return 0;
    }

    return round(getLevelSum() / getCurrentSize());
}

/**
    * @return   :  The integer count of tame Creatures in the Cavern
**/
int Cavern::getTameCount() const {
    return tame_count_;
}

/**
    * @return   :  The percentage (double) of all the tame creatures in the Cavern
    * @post     :   Computes the percentage of tame creatures in the Cavern rounded up to 2 decimal places.
**/
double Cavern::calculateTamePercentage() const {
    if (getCurrentSize() == 0) {
        return 0.0;
    }

    double percentage = (static_cast<double>(getTameCount()) / getCurrentSize()) * 100.0;
    return ceil(percentage * 100) / 100.0;
}


/**
    * @param   :  A reference to a string representing a creature Category with value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"]
    * @return  :  An integer tally of the number of creatures in the Cavern of the given category. 
                  If the argument string does not match one of the expected category values, the tally is zero. 
                  NOTE: no pre-processing of the input string necessary, only uppercase input will match.
**/
int Cavern::tallyCategory(const std::string& category) const {
    int tally = 0;
    
    for (int i = 0; i < item_count_; i++){
        Creature creature = items_[i];
        tally += creature.getCategory() == category;
    }

    return tally;
}

/**
    * @param  :   An integer representing the level threshold of the creatures to be removed from the Cavern, with default value 0
    * @post   :   Removes all creatures from the Cavern whose level is less than the given level. If no level is given, removes all creatures from the Cavern. Ignore negative input.
    * @return :   The number of creatures removed from the Cavern
*/
int Cavern::releaseCreaturesBelowLevel(const int level) {
    int removedCount = 0;

    if (level < 0) {
        return removedCount;
    }

    int size = getCurrentSize();
    for (int i = 0; i < size; i++) {
        if (level == 0 || items_[i].getLevel() < level) {
            if (exitCavern(items_[i])) {
                removedCount++;
                i--;
                size--;
            }
        }
    }

    return removedCount;
}

/**
    * @param  : A reference to a string representing a creature Category with a value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"], or default value "ALL" if no category is given
    * @post   : Removes all creatures from the Cavern whose category matches the given category. If no category is given, removes all creatures from the Cavern.
    * @return : The number of creatures removed from the Cavern
                NOTE: no pre-processing of the input string necessary, only uppercase input will match. If the input string does not match one of the expected category values, do not remove any creatures.
*/
int Cavern::releaseCreaturesOfCategory(const std::string& category) {
    int removedCount = 0;

    for (int i = 0; i < getCurrentSize(); i++) {
        if (category == "ALL" || items_[i].getCategory() == category) {
            if (remove(items_[i])) {
                removedCount++;
            }
        }
    }

    return removedCount;
}

/**
    * @post    : Outputs a report of the creatures currently in the Cavern in the form:
                "UNKNOWN: [x]\nUNDEAD: [x]\nMYSTICAL: [x]\nALIEN: [x]\n\nAVERAGE LEVEL: [x]\nTAME:[x]%\n"
                Note that the average level should be rounded to the NEAREST integer, and the percentage of tame creatures in the Cavern should be rounded to 2 decimal places.

                Example output: 
                UNKNOWN: 1
                UNDEAD: 3
                MYSTICAL: 2
                ALIEN: 1

                AVERAGE LEVEL: 5
                TAME: 85.72%
*/
void Cavern::cavernReport() const {

    std::cout << "UNKNOWN: " << this->tallyCategory("UNKNOWN") << "\n";
    std::cout << "UNDEAD: " << this->tallyCategory("UNDEAD") << "\n";
    std::cout << "MYSTICAL: " << this->tallyCategory("MYSTICAL") << "\n";
    std::cout << "ALIEN: " << this->tallyCategory("ALIEN") << "\n";
    std::cout << "\n";

    std::cout << "AVERAGE LEVEL: " << calculateAvgLevel() << "\n";
    std::cout << "TAME: " << calculateTamePercentage() << "%" << std::endl;
}
