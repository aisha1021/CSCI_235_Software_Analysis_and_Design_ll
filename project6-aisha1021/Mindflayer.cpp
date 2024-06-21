/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 6  - Creature Training! 
*/

#include "Mindflayer.hpp"

Mindflayer::Mindflayer() : affinities_{}, summoning_{false}, projectiles_{}
{
    setCategory(ALIEN);
}

Mindflayer::Mindflayer(const std::string& name, Category category, int hitpoints, int level, bool tame, std::vector<Projectile> projectiles, bool summoning, std::vector<Variant> affinities) : Creature(name, category, hitpoints, level, tame)
{
    setProjectiles(projectiles);
    summoning_ = summoning;
    setAffinities(affinities);
}

std::vector<Mindflayer::Projectile> Mindflayer::getProjectiles() const
{
    return projectiles_;
}

void Mindflayer::setProjectiles(const std::vector<Projectile>& projectiles)
{
    std::vector<Projectile> temp;
    for(int i = 0; i < projectiles.size(); i++)
    {
        bool found = false;
        for(int j = 0; j < temp.size(); j++)
        {
            if(projectiles[i].type_ == temp[j].type_)
            {
                if(projectiles[i].quantity_ > 0)
                {
                    temp[j].quantity_ += projectiles[i].quantity_;
                    found = true;
                }
            }
        }
        if(!found)
        {
            if(projectiles[i].quantity_ > 0)
            {
                temp.push_back(projectiles[i]);
            }
        }
    }
    projectiles_ = temp;
}

void Mindflayer::setSummoning(const bool& summoning)
{
    summoning_ = summoning;
}

bool Mindflayer::getSummoning() const
{
    return summoning_;
}

std::vector<Mindflayer::Variant> Mindflayer::getAffinities() const
{
    return affinities_;
}

void Mindflayer::setAffinities(const std::vector<Variant>& affinities)
{
    std::vector<Variant> temp;
    for(int i = 0; i < affinities.size(); i++)
    {
        bool found = false;
        for(int j = 0; j < temp.size(); j++)
        {
            if(affinities[i] == temp[j])
            {
                found = true;
            }
        }
        if(!found)
        {
            temp.push_back(affinities[i]);
        }
    }
    affinities_ = temp;
}

std::string Mindflayer::variantToString(const Variant& variant) const
{
    switch(variant)
    {
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



void Mindflayer::display() const{
    std::cout << "MINDFLAYER - " << getName() << std::endl;
    std::cout << "CATEGORY: " << getCategory() << std::endl;
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
    std::cout << "SUMMONING: " << (getSummoning() ? "TRUE" : "FALSE") << std::endl;
    for(int i = 0; i < projectiles_.size(); i++)
    {
        std::cout << variantToString(projectiles_[i].type_) << ": " << projectiles_[i].quantity_ << std::endl;
    }
    if(affinities_.size() > 0)
    {
        std::cout << "AFFINITIES: " << std::endl;
        for(int i = 0; i < affinities_.size(); i++)
        {
            std::cout << variantToString(affinities_[i]) << std::endl;
        }
    }
}

/**
    @post   : If the creature is UNDEAD, it becomes tame if not already, as it appreciates the gesture, even though as an UNDEAD it does not really eat. It gains 1 hitpoint from the mysterious powers it receives by wearing the mushroom as a hat. Nothing else happens.
                If the creature is MYSTICAL, if it can summon a Thoughtspawn, it gives the mushroom to the Thoughtspawn instead. Nothing else happens.
                If it cannot summon a Thoughtspawn and is tame, it eats the mushroom to be polite. If it only had 1 hitpoint left, it remains at 1 hitpoint and becomes untame, else it loses 1 hitpoint. Nothing else happens.
                If it cannot summon a Thoughtspawn and is untame, it decides it doesn't have to deal with this and it leaves the Cavern. Nothing else happens.
                If the creature is an ALIEN, if it has Telepathic affinity, it convinces Selfa Ensert to eat the mushroom instead, and gains 1 hitpoint from laughing at their resulting illness (as laughter is good for the soul).
                If it is an ALIEN and does not have Telepathic affinity, but has a Telepathic projectile, it uses one of its Telepathic projectiles to achieve the same effect. (Remember to remove the projectile from the vector if it only had 1 left)
                If it is an ALIEN and does not have Telepathic affinity or a Telepathic projectile, it eats the mushroom and gains 2 hitpoints. As it turns out, the mushroom was good for it. It becomes tame if it was not already. Nothing else happens.
    @return   : true if the creature leaves the Cavern, false otherwise
*/
bool Mindflayer::eatMycoMorsel(){
    if(getCategory() == "UNDEAD")
    {
        setTame(true);
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "MYSTICAL")
    {
        if(getSummoning())
        {
            return false;
        }
        else if(isTame())
        {
            if(getHitpoints() == 1)
            {
                setTame(false);
                return false;
            }
            else
            {
                setHitpoints(getHitpoints() - 1);
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    else if(getCategory() == "ALIEN")
    {
        bool telepathic = false;
        for(int i = 0; i < affinities_.size(); i++)
        {
            if(affinities_[i] == TELEPATHIC)
            {
                telepathic = true;
            }
        }
        bool telepathicProjectile = false;
        for(int i = 0; i < projectiles_.size(); i++)
        {
            if(projectiles_[i].type_ == TELEPATHIC)
            {
                telepathicProjectile = true;
                if(projectiles_[i].quantity_ == 1)
                {
                    projectiles_.erase(projectiles_.begin() + i);
                }
                else
                {
                    projectiles_[i].quantity_--;
                }
            }
        }
        if(telepathic || telepathicProjectile)
        {
            setHitpoints(getHitpoints() + 1);
            return false;
        }
        else
        {
            setTame(true);
            setHitpoints(getHitpoints() + 2);
            return false;
        }
    }
    else
    {
        return false;
    }

}

/**
* @param: A const reference to int corresponding to the attack to be added to the attack queue.
* @post: Adds an attack to the attack queue based on the int parameter.
* Here are the attacks for the Mindflayer:
*
* 1: PSIONIC BOLT/TENTACLE SLAP
*  If the Mindflayer has a PSIONIC projectile:
*      Attack name: PSIONIC BOLT
*      If the Mindflayer has a PSIONIC affinity:
*          Damage: 3 PSIONIC
*      Else:
*          Damage: 2 PSIONIC
* If the Mindflayer does not have a PSIONIC projectile:
*     Attack name: TENTACLE SLAP
*     Damage: 1 PHYSICAL, 1 EMOTIONAL
*
* 2: TELEPATHIC BOLT/TENTACLE SLAP
* If the Mindflayer has a TELEPATHIC projectile:
*      Attack name: TELEPATHIC BOLT
*      If the Mindflayer has a TELEPATHIC affinity:
*      Damage: 3 TELEPATHIC
*      Else:
*          Damage: 2 TELEPATHIC
* If the Mindflayer does not have a TELEPATHIC projectile:
*      Attack name: TENTACLE SLAP
*      Damage: 1 PHYSICAL, 1 EMOTIONAL
*
* 3: ILLUSIONARY BOLT/TENTACLE SLAP
* If the Mindflayer has an ILLUSIONARY projectile:
*      Attack name: ILLUSIONARY BOLT
*      If the Mindflayer has an ILLUSIONARY affinity:
*          Damage: 3 ILLUSIONARY
*      Else:
*          Damage: 2 ILLUSIONARY
* If the Mindflayer does not have an ILLUSIONARY projectile:
*      Attack name: TENTACLE SLAP
*      Damage: 1 PHYSICAL, 1 EMOTIONAL
* 
*/
void Mindflayer::addAttack(const int& attack_index) {
    Attack mindflayer_attack; // create an instance of the Attack struct to store the properties of the mindflayer's attack.

    switch (attack_index) { // select the attack based on the attack index
        case 1: {
            bool foundProjectile = false;
            bool foundAffinity = false;

            for (int i = 0; i < projectiles_.size(); i++) { // check if the Mindflayer has a PSIONIC projectile
                if (projectiles_[i].type_ == PSIONIC) {
                    mindflayer_attack.name_ = "PSIONIC BOLT";
                    foundProjectile = true;
                    break;
                }
            }

            for (int i = 0; i < affinities_.size(); i++) { // check if the Mindflayer has a PSIONIC affinity
                if (affinities_[i] == PSIONIC) {
                    foundAffinity = true;
                    break;
                }
            }

            if (foundProjectile) { // set attack properties based on the presence of projectile and affinity
                if (foundAffinity) {
                    mindflayer_attack.type_.push_back("PSIONIC");
                    mindflayer_attack.damage_.push_back(3);
                } else {
                    mindflayer_attack.type_.push_back("PSIONIC");
                    mindflayer_attack.damage_.push_back(2);
                }
            } else {
                mindflayer_attack.name_ = "TENTACLE SLAP";
                mindflayer_attack.type_.push_back("PHYSICAL");
                mindflayer_attack.damage_.push_back(1);
                mindflayer_attack.type_.push_back("EMOTIONAL");
                mindflayer_attack.damage_.push_back(1);
            }
            break;
        }
        case 2: {
            bool foundProjectile = false;
            bool foundAffinity = false;

            for (int i = 0; i < projectiles_.size(); i++) { // check if the Mindflayer has a TELEPATHIC projectile
                if (projectiles_[i].type_ == TELEPATHIC) {
                    mindflayer_attack.name_ = "TELEPATHIC BOLT";
                    foundProjectile = true;
                    break;
                }
            }

            for (int i = 0; i < affinities_.size(); i++) { // check if the Mindflayer has a TELEPATHIC affinity
                if (affinities_[i] == TELEPATHIC) {
                    foundAffinity = true;
                    break;
                }
            }

            if (foundProjectile) { // set attack properties based on the presence of projectile and affinity
                if (foundAffinity) {
                    mindflayer_attack.type_.push_back("TELEPATHIC");
                    mindflayer_attack.damage_.push_back(3);
                } else {
                    mindflayer_attack.type_.push_back("TELEPATHIC");
                    mindflayer_attack.damage_.push_back(2);
                }
            } else {
                mindflayer_attack.name_ = "TENTACLE SLAP";
                mindflayer_attack.type_.push_back("PHYSICAL");
                mindflayer_attack.damage_.push_back(1);
                mindflayer_attack.type_.push_back("EMOTIONAL");
                mindflayer_attack.damage_.push_back(1);
            }
            break;
        }
        case 3: {
            bool foundProjectile = false;
            bool foundAffinity = false;

            for (int i = 0; i < projectiles_.size(); i++) { // check if the Mindflayer has an ILLUSIONARY projectile
                if (projectiles_[i].type_ == ILLUSIONARY) {
                    mindflayer_attack.name_ = "ILLUSIONARY BOLT";
                    foundProjectile = true;
                    break;
                }
            }

            for (int i = 0; i < affinities_.size(); i++) { // check if the Mindflayer has an ILLUSIONARY affinity
                if (affinities_[i] == ILLUSIONARY) {
                    foundAffinity = true;
                    break;
                }
            }

            if (foundProjectile) { // set attack properties based on the presence of projectile and affinity
                if (foundAffinity) {
                    mindflayer_attack.type_.push_back("ILLUSIONARY");
                    mindflayer_attack.damage_.push_back(3);
                } else {
                    mindflayer_attack.type_.push_back("ILLUSIONARY");
                    mindflayer_attack.damage_.push_back(2);
                }
            } else {
                mindflayer_attack.name_ = "TENTACLE SLAP";
                mindflayer_attack.type_.push_back("PHYSICAL");
                mindflayer_attack.damage_.push_back(1);
                mindflayer_attack.type_.push_back("EMOTIONAL");
                mindflayer_attack.damage_.push_back(1);
            }
            break;
        }
    }

    attack_queue_.push(mindflayer_attack); // add the constructed attack to the attack queue
}

/**
  @post     : displays the attacks of the Mindflayer in the form:
  [MINDFLAYER] Choose an attack (1-3):\n1: PSIONIC BOLT\t\t2: TELEPATHIC BOLT\t\t3: ILLUSIONARY BOLT\n
*/
void Mindflayer::displayAttacks() const {
    std::cout << "[MINDFLAYER] Choose an attack (1-3):\n1: PSIONIC BOLT\t\t2: TELEPATHIC BOLT\t\t3: ILLUSIONARY BOLT\n"; // display attacks in this format
}