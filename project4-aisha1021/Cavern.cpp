/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 4 - The MycoMorsel
*/

#include "Cavern.hpp"

/**
  Default constructor.
  Default-initializes all private members. 
*/
Cavern::Cavern() : ArrayBag<Creature*>(), level_sum_{0}, tame_count_{0} {
}

/** 
  * @param   :   A Creature entering the Cavern
  * @post    :   If the given Creature is not already in the Cavern, add Creature to the Cavern and updates the level sum and the tame Creature count if the creature is tame.
  * @return  :   returns true if a Creature was successfully added to the Cavern (i.e. items_), false otherwise
            :   Hint: Use the above definition of equality will help determine if a Creature is already in the Cavern
**/
bool Cavern::enterCavern(Creature* const new_creature) {
  if (getIndexOf(new_creature) == -1) {
    if (add(new_creature)) {
      level_sum_ += new_creature->getLevel(); // Changed "." specifier to "->" when accessing member functions or variables of the new creature object
      if (new_creature->isTame()) {
        tame_count_++;
      }
      return true;
    }
  }
  return false;
}

/** 
  * @param   :   A Creature leaving the Cavern
  * @return  :  returns true if a creature was successfully removed from the Cavern (i.e. items_), false otherwise
  * @post    :    removes the creature from the Cavern and updates the level sum and the tame count if the creature is tame.
**/
bool Cavern::exitCavern(Creature* const creature_to_remove) {
  if (remove(creature_to_remove)) {
    level_sum_ -= creature_to_remove->getLevel(); // Changed "." specifier to "->" when accessing member functions or variables of the new creature object
    if (creature_to_remove->isTame()) {
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
  * @return   :  The average level of all the creatures in the Cavern
  * @post     :    Computes the average level of the Cavern rounded to the NEAREST integer.
**/
int Cavern::calculateAvgLevel() const {
  if (isEmpty()) {
    return 0;
  }
  return round(level_sum_ / getCurrentSize());
}

/**
  * @return   :  The integer count of tame Creatures in the Cavern
**/
int Cavern::getTameCount() const {
  return tame_count_;
}

/**
  * @return   :  The percentage (double) of all the tame creatures in the Cavern
  * @post     :    Computes the percentage of tame creatures in the Cavern rounded up to 2 decimal places.
**/
double Cavern::calculateTamePercentage() const {
  if (isEmpty()) {
    return 0;
  }
  double tame_percent = (tame_count_>0) ?  (double(tame_count_) / item_count_) * 100: 0.0;
  // return the tame percentage rounded up to two decimal places

  return std::ceil(tame_percent * 100) / 100;
}

/**
  * @param  :   A string representing a creature Category with value in 
              ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"]
  * @return  :  An integer tally of the number of creatures in the Cavern of the given category. 
              If the argument string does not match one of the expected category values, 
              the tally is zero. 
              NOTE: no pre-processing of the input string necessary, only uppercase input will match.
**/
int Cavern::tallyCategory(const std::string& category) const {
  if (category != "UNKNOWN" && category != "UNDEAD" && category != "MYSTICAL" && category != "ALIEN") {
    return 0;
  }
  int count = 0;
  for (int i = 0; i < getCurrentSize(); i++) {
    if (items_[i]->getCategory() == category) {
      count++;
    }
  }
  return count;
}

/**
    @param  :   An integer representing the level treshold of the creatures to be removed from the Cavern, with default value 0
    @post   :   Removes all creatures from the Cavern whose level is less than the given level. If no level is given, removes all creatures from the Cavern. Ignore negative input.
    @return :   The number of creatures removed from the Cavern
*/
int Cavern::releaseCreaturesBelowLevel(int level) {
  int count = 0;
  if (level < 0) {
    return 0;
  } else if (level == 0) {
    count = getCurrentSize();
    clear();
    return count;
  } else {
    int size = getCurrentSize();
    for (int i = 0; i < size; i++) {
      if (items_[i]->getLevel() < level) {
        exitCavern(items_[i]);
        count++;
      }
    }
    return count;
  }
}

/**
    @param  : A string representing a creature Category with a value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"], or default value "ALL" if no category is given
    @post   : Removes all creatures from the Cavern whose category matches the given category. If no category is given, removes all creatures from the Cavern.
    @return : The number of creatures removed from the Cavern
              NOTE: no pre-processing of the input string necessary, only uppercase input will match. If the input string does not match one of the expected category values, do not remove any creatures.
*/
int Cavern::releaseCreaturesOfCategory(const std::string& category) {
  int count = 0;
  if (category == "ALL") {
    count = getCurrentSize();
    clear();
    return count;
  } else if (category != "UNKNOWN" && category != "UNDEAD" && category != "MYSTICAL" && category != "ALIEN") {
    return 0;
  } else {
    int size = getCurrentSize();
    for (int i = 0; i < size; i++) {
    if (items_[i]->getCategory() == category) {
      exitCavern(items_[i]);
      count++;
    }
  }
  return count;
  }
}

/**
  * @post    : Outputs a report of the creatures currently in the Cavern in the form:
              "UNKNOWN: [x]\nUNDEAD: [x]\nMYSTICAL: [x]\nALIEN: [x]\n\nThe average level is: [x] \n[x]% are tame.\n"
              Note that the average level should be rounded to the NEAREST integer, and the percentage of tame creatures in the Cavern should be rounded to 2 decimal places.

              Example output: 
              UNKNOWN: 3
              UNDEAD: 5
              MYSTICAL: 8
              ALIEN: 6

              AVERAGE LEVEL: 7
              TAME: 46.67%
*/
void Cavern::cavernReport() const {
  std::cout << "UNKNOWN: " << tallyCategory("UNKNOWN") << std::endl;
  std::cout << "UNDEAD: " << tallyCategory("UNDEAD") << std::endl;
  std::cout << "MYSTICAL: " << tallyCategory("MYSTICAL") << std::endl;
  std::cout << "ALIEN: " << tallyCategory("ALIEN") << std::endl;
  std::cout << std::endl;

  std::cout << "AVERAGE LEVEL: " << calculateAvgLevel() << std::endl;
  std::cout << "TAME: " << calculateTamePercentage() << "%" << std::endl;
}

/**
    @param: the name of an input file (a string reference)
    @pre: Formatting of the csv file is as follows (each numbered item appears separated by comma, only one value for each numbered item):
    1. TYPE: An uppercase string [DRAGON, GHOUL, MINDFLAYER]
    2. NAME: An uppercase string
    3. CATEGORY: An uppercase string [ALIEN, MYSTICAL, UNDEAD]
    4. HITPOINTS: A positive integer
    5. LEVEL: A positive integer
    6. TAME: 0 (False) or 1 (True)
    7. ELEMENT/FACTION: Uppercase string or strings representing the ELEMENT (For Dragons), or FACTION (For Ghouls) of the creature. If the creature is of a different subclass, the value will be NONE
    8. HEADS: A positive integer of the number of heads the Dragon has. If the creature is of a different subclass, the value will be 0
    9. FLIGHT/TRANSFORM/SUMMONING: 0 (False) or 1 (True) representing if the creature can fly (Dragons), transform (Ghouls), or summon a Thoughtspawn (Mindflayers).
    10. DECAY: A non-negative integer representing the level of decay of the Ghoul. If the creature is of a different subclass, the value will be 0
    11. AFFINITIES: Only applicable to Mindflayers. Affinities are of the form [AFFINITY1];[AFFINITY2] where multiple affinities are separated by a semicolon. Th value may be NONE for a Mindflayer with no affinities, or creatures of other subclasses.
    12. PROJECTILES: Only applicable to Mindflayers. PROJECTILES are of the form [PROJECTILE TYPE1]-[QUANTITY];[PROJECTILE TYPE 2]-[QUANTITY] where multiple types of projectiles are separated by a semicolon. The value may be NONE for a Mindflayer with no projectiles, or creatures of other subclasses.
*/
Cavern::Cavern(const std::string & file_path) : ArrayBag<Creature*>(), level_sum_(0), tame_count_(0) {
    // Open the file
    std::ifstream file(file_path);
    std::string line, type, name, category, element_faction, hitpoints_str, level_str, heads_str, decay_str, tame_str, summoning_str, affinities_str, projectiles_str; 
    int hitpoints, level, heads, decay;
    bool tame, summoning; 

    // Sample variables for each type
    Creature::Category category_sample;
    Dragon::Element element_sample;
    Ghoul::Faction faction_sample;
    std::vector<Mindflayer::Variant> affinities_sample; 
    std::vector<Mindflayer::Projectile> projectiles_sample;

    // Skipping header line
    std::getline(file, line);

    // Loop through each line in the file
    while(std::getline(file, line)) {
        std::istringstream ss(line);

        // Parsing each line
        std::getline(ss, type, ',');
        std::getline(ss, name, ',');
        std::getline(ss, category, ',');
        std::getline(ss, hitpoints_str, ',');
        std::getline(ss, level_str, ',');
        std::getline(ss, tame_str, ',');
        std::getline(ss, element_faction, ',');
        std::getline(ss, heads_str, ',');
        std::getline(ss, summoning_str, ',');
        std::getline(ss, decay_str, ',');
        std::getline(ss, affinities_str, ',');
        std::getline(ss, projectiles_str, ',');

        // Convert string values to appropriate types
        std::istringstream(hitpoints_str) >> hitpoints;
        std::istringstream(level_str) >> level;
        std::istringstream(heads_str) >> heads;
        std::istringstream(decay_str) >> decay;

        tame = (tame_str == "0" ? false : true);
        summoning = (summoning_str == "0" ? false : true);

        // Determine the category of the creature
        if(category == "UNKNOWN") {
            category_sample = Creature::UNKNOWN;
        } else if(category == "UNDEAD") {
            category_sample = Creature::UNDEAD;
        } else if(category == "MYSTICAL") {
            category_sample = Creature::MYSTICAL;
        } else if(category == "ALIEN") {
            category_sample = Creature::ALIEN;
        }

        // Creating different types of creatures based on the parsed data
        if(type == "DRAGON") {
            // Creating a Dragon
            if(element_faction == "NONE") {
                element_sample = Dragon::NONE;
            } else if(element_faction == "FIRE") {
                element_sample = Dragon::FIRE;
            } else if(element_faction == "WATER") {
                element_sample = Dragon::WATER;
            } else if(element_faction == "EARTH") {
                element_sample = Dragon::EARTH;
            } else if(element_faction == "AIR") {
                element_sample = Dragon::AIR;
            }

            Dragon* dragon = new Dragon(name, category_sample, hitpoints, level, tame, element_sample, heads, summoning);
            // Add the created Dragon to the Cavern
            enterCavern(dragon);
        } else if(type == "GHOUL") {
            // Creating a Ghoul
            if(element_faction == "NONE") {
                faction_sample = Ghoul::NONE;
            } else if(element_faction == "FLESHGORGER") {
                faction_sample = Ghoul::FLESHGORGER;
            } else if(element_faction == "SHADOWSTALKER") {
                faction_sample = Ghoul::SHADOWSTALKER;
            } else if(element_faction == "PLAGUEWEAVER") {
                faction_sample = Ghoul::PLAGUEWEAVER;
            }

            Ghoul* ghoul = new Ghoul(name, category_sample, hitpoints, level, tame, decay, faction_sample, summoning);
            // Add the created Ghoul to the Cavern
            enterCavern(ghoul);
        } else if(type == "MINDFLAYER") {
            // Creating a Mindflayer
            affinities_sample.clear();
            projectiles_sample.clear();
            std::istringstream affinities_stream(affinities_str);
            std::string halt_affinities; 

            // Parsing Mindflayer affinities
            while(std::getline(affinities_stream, halt_affinities, ';')) {
                if(halt_affinities == "PSIONIC") {
                    affinities_sample.push_back(Mindflayer::PSIONIC);
                } else if(halt_affinities == "TELEPATHIC") {
                    affinities_sample.push_back(Mindflayer::TELEPATHIC);
                } else if(halt_affinities == "ILLUSIONARY") {
                    affinities_sample.push_back(Mindflayer::ILLUSIONARY);
                }
            }

            std::istringstream projectiles_stream(projectiles_str);
            std::string halt_projectiles; 

            // Parsing Mindflayer projectiles
            while(std::getline(projectiles_stream, halt_projectiles, ';')) {
                std::string variant_type, string_quantity; 
                int variant_quantity; 
                std::istringstream ps(halt_projectiles);

                std::getline(ps, variant_type, '-');
                std::getline(ps, string_quantity, '-');

                std::istringstream ch(string_quantity);
                ch >> variant_quantity; 

                if(variant_type == "PSIONIC") {
                    projectiles_sample.push_back({ Mindflayer::PSIONIC, variant_quantity});
                } else if(variant_type == "TELEPATHIC") {
                    projectiles_sample.push_back({ Mindflayer::TELEPATHIC, variant_quantity});
                } else if(variant_type == "ILLUSIONARY") {
                    projectiles_sample.push_back({ Mindflayer::ILLUSIONARY, variant_quantity});
                }
            }

            // Create the Mindflayer with the parsed data
            Mindflayer* mindflayer = new Mindflayer(name, category_sample, hitpoints, level, tame, projectiles_sample, summoning, affinities_sample);
            // Add the created Mindflayer to Cavern
            enterCavern(mindflayer);
        }
    }
    // Close the file
    file.close();
}

/**
    @param: The output stream to write the creature's information to.
    @param: The creature object whose information is to be written.
    @post Displays the information of the creature to the output stream.
*/
std::ostream& operator<<(std::ostream& os, const Creature& creature) {
    // Cast the creature to Dragon type
    if (const Dragon* dragon = dynamic_cast<const Dragon*>(&creature)) {
        dragon->display(); // If successful, display Dragon information
    } 
    // If not a Dragon, cast to Ghoul type
    else if (const Ghoul* ghoul = dynamic_cast<const Ghoul*>(&creature)) {
        ghoul->display(); // If successful, display Ghoul information
    } 
    // If not a Ghoul, cast to Mindflayer type
    else if (const Mindflayer* mindflayer = dynamic_cast<const Mindflayer*>(&creature)) {
        mindflayer->display(); // If successful, display Mindflayer information
    } 
    // If none of the above types, treat as unknown creature
    else {
        os << "UNKNOWN CREATURE" << std::endl; // Display unknown creature message
    }

    return os; // Return the output stream
}

/**
    @post: For every creature in the cavern, displays each creature's information
*/
void Cavern::displayCreatures() const {
    // Loop through all items in the cavern
    for (size_t i = 0; i < item_count_; i++) {
        // Get a pointer to the current creature
        const Creature* creature_ptr = items_[i];
        // Check if the pointer is not null
        if (creature_ptr != nullptr) {
            // If not null, dereference the pointer and use overloaded << operator to display creature information
            std::cout << *creature_ptr << std::endl;
        }
    }
}

/**
    @param: a string reference to a category
    @post: For every creature in the cavern of the given category (only exact matches to the input string), displays each creature's information

*/
void Cavern::displayCategory(const std::string& category) const {
    // Loop through all items in the cavern
    for (size_t i = 0; i < item_count_; i++) {
        // Get a pointer to the current creature
        const Creature* creature_ptr = items_[i];
        // Check if the pointer is not null and if the creature's category matches the specified category
        if (creature_ptr != nullptr && creature_ptr->getCategory() == category) {
            // If conditions are met, dereference the pointer and use overloaded << operator to display creature information
            std::cout << *creature_ptr << std::endl;
        }
    }
}

/**
    @post: Every creature in the cavern eats a MycoMorsel.
*/
void Cavern::mycoMorselFeast() {
    // Loop through all items in the cavern
    for (size_t i = 0; i < item_count_; i++) {
        // Get a pointer to the current creature
        Creature* creature_ptr = items_[i];
        // Check if the pointer is not null
        if (creature_ptr != nullptr) {
            // If not null, call the eatMycoMorsel() function on the creature
            creature_ptr->eatMycoMorsel();
        }
    }
}
