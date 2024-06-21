/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 4 - The MycoMorsel
*/

#include "Mindflayer.hpp"

/**
    Default constructor.
    Default-initializes all private members. 
    Default Category: ALIEN
    Default summoning: False
*/
Mindflayer::Mindflayer() : affinities_{}, summoning_{false}, projectiles_{} {
    setCategory(ALIEN);
}

/**
    Parameterized constructor.
    @param      : A reference to the name of the Mindflayer (a string)
    @param      : The category of the Mindflayer (a Category enum) with default value ALIEN
    @param      : The Mindflayer's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : The Mindflayer's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : A flag indicating whether the Mindflayer is tame, with default value False
    @param      : The projectiles (a vector of Projectile structs), with default value an empty vector if not provided
    @param      : A flag indicating whether the Mindflayer can summon a Thoughtspawn, with default value False
    @param      : The affinities (a vector of Variant enums), with default value an empty vector if not provided
    @post       : The private members are set to the values of the corresponding parameters.
    Hint: Notice the default arguments in the parameterized constructor.
*/
Mindflayer::Mindflayer(const std::string& name, Category category, int hitpoints, int level, bool tame, std::vector<Projectile> projectiles, bool summoning, std::vector<Variant> affinities) : Creature(name, category, hitpoints, level, tame) {
    setProjectiles(projectiles);
    summoning_ = summoning;
    setAffinities(affinities);
}

/**
    Getter for the projectiles.
    @return     : The projectiles (a vector of Projectile structs)
*/
std::vector<Mindflayer::Projectile> Mindflayer::getProjectiles() const {
    return projectiles_;
}

/**
    Setter for the projectiles.
    @param      : A reference to the projectiles (a vector of Projectile structs)
    @post       : The projectiles are set to the value of the parameter. There should not be any duplicate projectiles in Mindflayer's projectiles vector.
                : For example, if the vector in the given parameter contains the following Projectiles: {{PSIONIC, 2}, {TELEPATHIC, 1}, {PSIONIC, 1}, {ILLUSIONARY, 3}}, 
                : the projectiles vector should be set to contain the following Projectiles: {{PSIONIC, 3}, {TELEPATHIC, 1}, {ILLUSIONARY, 3}}. 
                : If the quantity of a projectile is 0 or negative, it should not be added to the projectiles vector.
                : Note the order of the projectiles in the vector.
*/
void Mindflayer::setProjectiles(const std::vector<Projectile>& projectiles) {
    std::vector<Projectile> temp;
    for(int i = 0; i < projectiles.size(); i++) {
        bool found = false;
        for(int j = 0; j < temp.size(); j++) {
            if(projectiles[i].type_ == temp[j].type_) {
                if(projectiles[i].quantity_ > 0) {
                    temp[j].quantity_ += projectiles[i].quantity_;
                    found = true;
                }
            }
        }
        if(!found) {
            if(projectiles[i].quantity_ > 0) {
                temp.push_back(projectiles[i]);
            }
        }
    }
    projectiles_ = temp;
}

/**
    Setter for the summoning.
    @param      : A reference to the summoning (a boolean)
    @post       : The summoning is set to the value of the parameter.
*/
void Mindflayer::setSummoning(const bool& summoning) {
    summoning_ = summoning;
}

/**
    Getter for the summoning.
    @return     : The summoning (a boolean)
*/
bool Mindflayer::getSummoning() const {
    return summoning_;
}

/**
    Getter for the affinities.
    @return     : The affinities (a vector of Variant enums)
*/
std::vector<Mindflayer::Variant> Mindflayer::getAffinities() const {
    return affinities_;
}

/**
    Setter for the affinities.
    @param      : A reference to the affinities (a vector of Variant enums)
    @post       : The affinities are set to the value of the parameter.
                : There should not be any duplicate affinities in Mindflayer's affinities vector. 
                : For example, if the vector in the given parameter contains the following affinities: {PSIONIC, TELEPATHIC, PSIONIC, ILLUSIONARY}, 
                : the affinities vector should be set to contain the following affinities: {PSIONIC, TELEPATHIC, ILLUSIONARY}.
                : Note the order of the affinities in the vector.
*/
void Mindflayer::setAffinities(const std::vector<Variant>& affinities) {
    std::vector<Variant> temp;
    for(int i = 0; i < affinities.size(); i++) {
        bool found = false;
        for(int j = 0; j < temp.size(); j++) {
            if(affinities[i] == temp[j]) {
                found = true;
            }
        }
        if(!found) {
            temp.push_back(affinities[i]);
        }
    }
    affinities_ = temp;
}

/**
    @param       : A reference to the Variant 
    @return      : The string representation of the variant
*/
std::string Mindflayer::variantToString(const Variant& variant) const {
    switch(variant) {
        case PSIONIC:
            return "PSIONIC";
        case TELEPATHIC:
            return "TELEPATHIC";
        case ILLUSIONARY:
            return "ILLUSIONARY";
        default:
            return "NONE";
    }
}

/**
    @post     : displays Mindflayer data in the form:
    "MINDFLAYER - [NAME]\n
    CATEGORY: [CATEGORY]\n
    HP: [HITPOINTS]\n
    LVL: [LEVEL]\n
    TAME: [TRUE/FALSE]\n
    SUMMONING: [SUMMONING]\n
    [PROJECTILE TYPE 1]: [QUANTITY 1]\n
    [PROJECTILE TYPE 2]: [QUANTITY 2]\n
    AFFINITIES: \n
    [AFFINITY 1]\n
    [AFFINITY 2]\n"

    NOTE: For the Projectiles, print out the type and quantity of each projectile in the format: 
    [TYPE]: [QUANTITY] for each projectile in the vector, where the type is the string equivalent of the Variant (eg. "PSIONIC"/"TELEPATHIC"/"ILLUSIONARY"). If there are no projectiles, don't print anything. 

    For the Affinities, print out each affinity in the format: [AFFINITY 1]\n[AFFINITY 2]\n for each Affinity in the vector, where the Affinity is the string equivalent of the Variant (eg. "PSIONIC"/"TELEPATHIC"/"ILLUSIONARY"). If there are no affinities, don't print anything, including the label "AFFINITIES:". 
    
    Example:
    MINDFLAYER - JHOCTOPUS
    CATEGORY: UNDEAD
    HP: 3
    LVL: 6
    TAME: TRUE
    SUMMONING: TRUE
    PSIONIC: 2
    TELEPATHIC: 11
    AFFINITIES: 
    PSIONIC
    ILLUSIONARY
*/
void Mindflayer::display() const {
    std::cout << "MINDFLAYER - " << getName() << std::endl; // Display Mindflayer's name
    std::cout << "CATEGORY: " << getCategory() << std::endl; // Display Mindflayer's category
    std::cout << "HP: " << getHitpoints() << std::endl; // Display Mindflayer's hitpoints
    std::cout << "LVL: " << getLevel() << std::endl; // Display Mindflayer's level
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl; // Display whether Mindflayer is tame or not
    std::cout << "SUMMONING: " << (summoning_ ? "TRUE" : "FALSE") << std::endl; // Display whether Mindflayer can summon
    for (const auto& projectile : projectiles_) {
        std::cout << variantToString(projectile.type_) << ": " << projectile.quantity_ << std::endl; // Display Mindflayer's projectiles and their quantities
    }
    // Display Mindflayer's affinities
    if (!affinities_.empty()) {
        std::cout << "AFFINITIES: " << std::endl;
        for (const auto& affinity : affinities_) {
            std::cout << variantToString(affinity) << std::endl;
        }
    }
}


/**
    @post: 
    If the creature is UNDEAD, it becomes tame if not already, as it appreciates the gesture, even though as an 
    UNDEAD it does not really eat. It gains 1 hitpoint from the mysterious powers it receives by wearing the 
    mushroom as a hat. Nothing else happens.

    If the creature is MYSTICAL, if it can summon a Thoughtspawn, it gives the mushroom to the Thoughtspawn 
    instead. If it cannot summon a Thoughtspawn and is tame, it eats the mushroom to be polite. If it only had 1 
    hitpoint left, it remains at 1 hitpoint and becomes untame, else it loses 1 hitpoint. If it cannot summon a 
    Thoughtspawn and is untame, it decides it doesn't have to deal with this and it leaves the Cavern. Nothing else 
    happens.
    
    If the creature is an ALIEN, if it has Telepathic affinity, it convinces Selfa Ensert to eat the mushroom instead, 
    and gains 1 hitpoint from laughing at their resulting illness (as laughter is the best medicine).

    If it is an ALIEN and does not have Telepathic affinity, but has a Telepathic projectile, it uses one of such 
    projectile to achieve the same effect. (Remember to remove the projectile from the vector if it only had 1 left)

    If it is an ALIEN and does not have Telepathic affinity or a Telepathic projectile, it eats the mushroom and 
    gains 2 hitpoints. As it turns out, the mushroom was good for it. It becomes tame if it was not already. Nothing 
    else happens.

    @return   : true if the creature leaves the Cavern, false otherwise
*/
bool Mindflayer::eatMycoMorsel() {
    // Check if the Mindflayer is undead
    if(getCategory() == "UNDEAD"){
        setTame(true); // Make the Mindflayer tame
        setHitpoints(getHitpoints() + 1); // Increase hitpoints
        return false;
    }
    // Check if the Mindflayer is mystical
    else if(getCategory() == "MYSTICAL") {
        // If the Mindflayer can summon, do nothing
        if(getSummoning() == true) {
           return false;
        }
        // If the Mindflayer cannot summon and is tame
        else if(getSummoning() == false &&  isTame() == true) {   
            // If the Mindflayer has only 1 hitpoint, make it untame
            if(getHitpoints() == 1) {
                setTame(false); // Make the Mindflayer untame
            } else {
               setHitpoints(getHitpoints() - 1); // Decrease hitpoints
            }
            return false;  
        } 
        // If the Mindflayer cannot summon and is untame
        else if(getSummoning() == false && isTame() == false) {
            return true; // Return true indicating the Mindflayer leaves the Cavern
        }
    } 
    // Check if the Mindflayer is alien
    else if(getCategory() == "ALIEN") {
        bool has_affinity = false; // Flag to track if the Mindflayer has telepathic affinity
        bool has_project = false; // Flag to track if the Mindflayer has a telepathic projectile

        // Loop through the affinities to check for telepathic affinity
        for(int i = 0; i < getAffinities().size(); i++) {
            if (affinities_[i] == TELEPATHIC) {
                setHitpoints(getHitpoints() + 1); // Increase hitpoints if telepathic affinity is present
                has_affinity = true; // Set affinity flag to true
            }
        }
        // Loop through the projectiles to check for telepathic projectile
        for(int i= 0; i < getProjectiles().size(); i++){
            if(projectiles_[i].type_ == TELEPATHIC) {
                has_project = true; // Set project flag to true
                // If the Mindflayer has more than 1 telepathic projectile, decrease the quantity
                if(projectiles_[i].quantity_ > 1){
                    projectiles_[i].quantity_ --;
                } else {
                    projectiles_.erase(projectiles_.begin() + i); // If only 1, remove the projectile
                }
            }
        }
        // If the Mindflayer has telepathic affinity or telepathic projectile, increase hitpoints
        if(has_affinity == true || has_project == true) {
            setHitpoints(getHitpoints() + 1); // Increase hitpoints
            return false;
        }
        // If the Mindflayer has neither telepathic affinity nor telepathic projectile
        else {
            setTame(true); // Make the Mindflayer tame
            setHitpoints(getHitpoints() + 2); // Increase hitpoints
            return false; 
        }
    }
    return false; // Default case, should not be reached
}
