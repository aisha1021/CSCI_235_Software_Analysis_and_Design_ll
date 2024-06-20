/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 2 - Creature Types: Inheritance
*/

#include "Mindflayer.hpp"

/**
    Default constructor.
    Default-initializes all private members. 
    Default Category: ALIEN
    Default summoning: False
*/
Mindflayer::Mindflayer(): Creature("NAMELESS", ALIEN), summoning_{false} {}

/**
    Parameterized constructor.
    @param      : A reference to the name of the Mindflayer (a string)
    @param      : The category of the Mindflayer (a Category enum) with default value ALIEN
    @param      : The Mindflayer's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : The Mindflayer's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
    @param      : A flag indicating whether the Mindflayer is tame, with default value False
    @param      : The projectiles (a vector of Projectile structs), with default value an empty vector if not provided
    @param      : A flag indicating whether the Mindflayer can summon, with default value False
    @param      : The affinities (a vector of Variant enums), with default value an empty vector if not provided
    @post       : The private members are set to the values of the corresponding parameters.
    Hint: Notice the default arguments in the parameterized constructor.
*/
Mindflayer::Mindflayer(const std::string& name, Category category, int hitpoints, int level,
                       bool tame, const std::vector<Projectile>& projectiles, bool summoning,
                       const std::vector<Variant>& affinities):
                       Creature(name, category, hitpoints, level, tame), summoning_{summoning} {
    setProjectiles(projectiles);
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
    projectiles_.clear();

    for (size_t i = 0; i < projectiles.size(); i++) {
        const Projectile& projectile = projectiles[i];

        if (projectile.quantity_ <= 0) {
            continue;
        }

        bool foundDuplicate = false;
        for (size_t j = 0; j < projectiles_.size(); j++) {
            if (projectiles_[j].type_ == projectile.type_) {
                projectiles_[j].quantity_ += projectile.quantity_;
                foundDuplicate = true;
                break;
            }
        }

        if (!foundDuplicate) {
            projectiles_.push_back(projectile);
        }
    }
}

/**
    Getter for the summoning.
    @return     : The summoning (a boolean)
*/
bool Mindflayer::getSummoning() const {
    return summoning_;
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
    affinities_ = affinities;

    for (int i = 0; i < affinities_.size(); i++) {
        for (int j = i + 1; j < affinities_.size(); j++) {
            if (affinities_[i] == affinities_[j]) {
                affinities_.erase(affinities_.begin() + j);
                j--;
            }
        }
    }
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
            return "UNKNOWN";
    }
}