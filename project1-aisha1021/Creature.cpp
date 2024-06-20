/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
Project 1
*/

#include "Creature.hpp"

/**
    Default constructor.
    Default-initializes all private members. 
    Default creature name: "NAMELESS". 
    Booleans are default-initialized to False. 
    Default enum value: UNKNOWN 
    Default Hitpoints and Level: 1.
*/
Creature::Creature() 
    : name_("NAMELESS"), category_(UNKNOWN), hitpoints_(1), level_(1), is_tame_(false) {}

/**
Parameterized constructor.
    @param      : A reference to the name of the creature (a string). Set the creature's name to NAMELESS if the provided string contains non-alphabetic characters.
    @param      : The category of the creature (a Category enum) with default value UNKNOWN
    @param      : The creature's hitpoints (an integer) , with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : The creature's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : A flag indicating whether the creature is tame, with default value False
    @post       : The private members are set to the values of the corresponding parameters. The name is converted to UPPERCASE if it consists of alphabetical characters only, otherwise it is set to NAMELESS.
*/
Creature::Creature(const std::string& name, Category category, int hitpoints, int level, bool is_tame)
    : category_(category), hitpoints_(hitpoints > 0 ? hitpoints : 1), 
      level_(level > 0 ? level : 1), is_tame_(is_tame) {
    if (!setName(name)) {
        name_ = "NAMELESS";
    }
}
    
/**
    @param      : the name of the Creature, a reference to string
    @post       : sets the Creature's name to the value of the parameter in UPPERCASE. 
                (convert any lowercase character to uppercase)
                Only alphabetical characters are allowed. 
                : If the input contains non-alphabetic characters, do nothing.
    @return     : true if the name was set, false otherwise
*/
bool Creature::setName(const std::string& name) {
    std::string uppercaseName;

    for (char c : name) {
        if (isalpha(c)) {
            uppercaseName += toupper(c);
        }
    }

    if (!uppercaseName.empty()) {
        name_ = uppercaseName;
        return true;
    } else {
        return false;
    }
}

/**
    @return : the name of the Creature
*/
std::string Creature::getName() const {
    return name_;
}

/**
    @param  : a reference to Category, the category of the Creature (an enum)
    @post   : sets the Creature's category to the value of the parameter
            : If the given category was invalid, set category_ to UNKNOWN.
*/
void Creature::setCategory(const Category& category) {
    if (category >= UNKNOWN && category <= ALIEN) {
        category_ = category;
    } else {
        category_ = UNKNOWN; 
    }
}

/**
    @return : the category of the Creature (in string form)
*/
std::string Creature::getCategory() const {
    switch (category_) {
        case UNKNOWN:
            return "UNKNOWN";
        case UNDEAD:
            return "UNDEAD";
        case MYSTICAL:
            return "MYSTICAL";
        case ALIEN:
            return "ALIEN";
        default:
            return "UNKNOWN";
    }
}

/**
    @param  : a reference to integer that represents the creature's hitpoints
    @pre    : hitpoints >= 0 : Characters cannot have negative hitpoints 
              (do nothing for invalid input)
    @post   : sets the hitpoints private member to the value of the parameter
    @return : true if the hitpoints were set, false otherwise
*/
bool Creature::setHitpoints(const int& hitpoints) {
    if (hitpoints >= 0) {
        hitpoints_ = hitpoints;
        return true;
    }
    return false;
}

/**
    @return : the value stored in hitpoints_
*/
int Creature::getHitpoints() const {
    return hitpoints_;
}

/**
    @param  : a reference to integer level
    @pre    : level >= 0 : Characters cannot have a negative level
    @post   : sets the level private member to the value of the parameter 
             (do nothing for invalid input)
    @return : true if the level was set, false otherwise
*/
bool Creature::setLevel(const int& level) {
    if (level >= 0) {
        level_ = level;
        return true;
    }
    return false;
}

/**
    @return : the value stored in level_
*/
int Creature::getLevel() const {
    return level_;
}

/**
    @param  : a reference to boolean value
    @post   : sets the tame flag to the value of the parameter
*/
void Creature::setTame(const bool& is_tame) {
    is_tame_ = is_tame;
}

/**
    @return true if the creature is tame, false otherwise
    Note: this is an accessor function and must follow the same convention as all accessor functions even if it is not called getTame
*/
bool Creature::isTame() const {
    return is_tame_;
}

/**
    @post     : displays Creature data in the form:
              "[NAME]\n
               Category: [CATEGORY]\n
               Level: [LEVEL]\n
               Hitpoints: [Hitpoints]\n
               Tame: [TRUE/FALSE]"   
*/
void Creature::display() const {
    std::cout << name_ << "\n"
            << "Category: " << getCategory() << "\n"
            << "Level: " << getLevel() << "\n"
            << "Hitpoints: " << getHitpoints() << "\n"
            << "Tame: ";
    
    if (isTame()) {
        std::cout << "TRUE";
    } else {
        std::cout << "FALSE";
    }

    std::cout << std::endl;
}