/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 6  - Creature Training! 
*/

#include "Dragon.hpp"

Dragon::Dragon() : element_{NONE}, number_of_heads_{1}, flight_{false}
{
    setCategory(MYSTICAL); 
    
}


Dragon::Dragon(const std::string& name, Category category, int hitpoints, int level, bool tame, Element element, int number_of_heads, bool flight) : Creature(name, category, hitpoints, level, tame)
{
    element_ = element;
    if(!setNumberOfHeads(number_of_heads))
    {
        number_of_heads_ = 1;
    }
    flight_ = flight;
}

std::string Dragon::getElement() const
{
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

void Dragon::setElement(const Element& element)
{
    element_ = element;
}

int Dragon::getNumberOfHeads() const
{
    return number_of_heads_;
}

bool Dragon::setNumberOfHeads(const int& number_of_heads)
{
    if(number_of_heads > 0)
    {
        number_of_heads_ = number_of_heads;
        return true;
    }
    else
    {
        return false;
    }
}

bool Dragon::getFlight() const
{
    return flight_;
}

void Dragon::setFlight(const bool& flight)
{
    flight_ = flight;
}


void Dragon::display() const
{
    std::cout << "DRAGON - " << getName() << std::endl;
    std::cout << "CATEGORY: " << getCategory() << std::endl;
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
    std::cout << "ELEMENT: " << getElement() << std::endl;
    std::cout << "HEADS: " << getNumberOfHeads() << std::endl;
    std::cout << "IT " << (getFlight() ? "CAN" : "CANNOT") << " FLY" << std::endl;
}



bool Dragon::eatMycoMorsel()
{
    if(getCategory() == "UNDEAD")
    {
        setTame(true);
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "ALIEN")
    {
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "MYSTICAL")
    {
        if(getElement() == "FIRE" || getElement() == "EARTH")
        {
            setHitpoints(getHitpoints() + 1);
            return false;
        }
        else if(getHitpoints() == 1)
        {
            return true;
        }
        else
        {
            setHitpoints(getHitpoints() - 1);
            setTame(false);
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
  * Here are the attacks for the Dragon:
  
* 1: Attack name: BITE
*      if ALIEN: 4 PHYSICAL
*      if MYSTICAL: 2 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
*      if UNDEAD: 2 PHYSICAL, 1 POISON
*      if UNKNOWN: 2 PHYSICAL

* 2: Attack name: STOMP
*      if ALIEN: 2 PHYSICAL
*      if MYSTICAL: 1 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
*      if UNDEAD: 1 PHYSICAL, 1 POISON
*      if UNKNOWN: 1 PHYSICAL

* 3: Attack name: [ELEMENTAL BREATH/BAD BREATH], where the name is ELEMENTAL BREATH if the Dragon has an elemental affinity, otherwise it is BAD BREATH
*      if ALIEN: 6 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*      if MYSTICAL: 3 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*      if UNDEAD: 3 [POISON/FIRE/WATER/EARTH/AIR], 1 POISON. The damage types and amount are added to the vector as two separate entries, even if both entries are POISON type.
*      if UNKNOWN: 3 [POISON/FIRE/WATER/EARTH/AIR] where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON  
*/
void Dragon::addAttack(const int& attack_index) {
    Attack dragon_attack; // create an instance of the Attack struct to store the properties of the dragon's attack.


    switch (attack_index) { // select the attack based on the attack index
        case 1:
            dragon_attack.name_ = "BITE";
            if (getCategory() == "ALIEN") { // set attack properties based on category
                dragon_attack.type_.push_back("PHYSICAL");
                dragon_attack.damage_.push_back(4);
            } else if (getCategory() == "MYSTICAL") {
                dragon_attack.type_.push_back("PHYSICAL");
                dragon_attack.damage_.push_back(2);
                if (getElement() != "NONE") { // add additional damage if the dragon has an elemental affinity
                    dragon_attack.type_.push_back(getElement());
                    dragon_attack.damage_.push_back(1); // additional damage of 1
                }
            } else if (getCategory() == "UNDEAD") {
                dragon_attack.type_.push_back("PHYSICAL");
                dragon_attack.damage_.push_back(2);
                dragon_attack.type_.push_back("POISON");
                dragon_attack.damage_.push_back(1);
            } else { // UNKNOWN
                dragon_attack.type_.push_back("PHYSICAL");
                dragon_attack.damage_.push_back(2);
            }
            break;

        case 2:
            dragon_attack.name_ = "STOMP";
            if (getCategory() == "ALIEN") { // set attack properties based on category
                dragon_attack.type_.push_back("PHYSICAL");
                dragon_attack.damage_.push_back(2);
            } else if (getCategory() == "MYSTICAL") {
                dragon_attack.type_.push_back("PHYSICAL");
                dragon_attack.damage_.push_back(1);
                if (getElement() != "NONE") { // add additional damage if the dragon has an elemental affinity
                    dragon_attack.type_.push_back(getElement());
                    dragon_attack.damage_.push_back(1); // additional damage of 1
                }
            } else if (getCategory() == "UNDEAD") {
                dragon_attack.type_.push_back("PHYSICAL");
                dragon_attack.damage_.push_back(1);
                dragon_attack.type_.push_back("POISON");
                dragon_attack.damage_.push_back(1);
            } else { // UNKNOWN
                dragon_attack.type_.push_back("PHYSICAL");
                dragon_attack.damage_.push_back(1);
            }
            break;

        case 3:
            // Set attack name based on elemental affinity
            if (getElement() != "NONE") {
                dragon_attack.name_ = "ELEMENTAL BREATH";
                if (getCategory() == "ALIEN") { //sSet attack properties based on category
                    dragon_attack.type_.push_back(getElement());
                    dragon_attack.damage_.push_back(6);
                } else if (getCategory() == "MYSTICAL") {
                    dragon_attack.type_.push_back(getElement());
                    dragon_attack.damage_.push_back(3);
                } else if (getCategory() == "UNDEAD") {
                    dragon_attack.type_.push_back(getElement());
                    dragon_attack.damage_.push_back(3);
                    dragon_attack.type_.push_back("POISON");
                    dragon_attack.damage_.push_back(1);
                } else { // UNKNOWN
                    dragon_attack.type_.push_back(getElement());
                    dragon_attack.damage_.push_back(3);
                }
            } else {
                dragon_attack.name_ = "BAD BREATH";
                if (getCategory() == "ALIEN") { // set attack properties based on category
                    dragon_attack.type_.push_back("POISON");
                    dragon_attack.damage_.push_back(6);
                } else if (getCategory() == "MYSTICAL") {
                    dragon_attack.type_.push_back("POISON");
                    dragon_attack.damage_.push_back(3);
                } else if (getCategory() == "UNDEAD") {
                    dragon_attack.type_.push_back("POISON");
                    dragon_attack.damage_.push_back(3);
                    dragon_attack.type_.push_back("POISON");
                    dragon_attack.damage_.push_back(1);
                } else { // UNKNOWN
                    dragon_attack.type_.push_back("POISON");
                    dragon_attack.damage_.push_back(3);
                }
            }
            break;
    }

    attack_queue_.push(dragon_attack); // add the constructed attack to the attack queue
}

/**
  * @post: Displays available attacks and promps the user to enter 2 numbers in the range [1,3]
  *        Print in the following form:
  *        [DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n
*/
void Dragon::displayAttacks() const {
    std::cout << "[DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n"; // display attacks in this format
}