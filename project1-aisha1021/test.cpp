/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
Project 1
*/

#include "Creature.hpp"

int main() {

    /**  
        2.1 
            - Instantiate a creature with the default constructor
            - Set its hitpoints to 10 using the appropriate setter function.
            - Set its level to 5 using the appropriate setter functions
            - Set its tame flag to True using the appropriate setter function.

            - Print out the creature's information using the display() function:

            Expected output:
            NAMELESS
            Category: UNKNOWN
            Level: 5
            Hitpoints: 10
            Tame: TRUE
    */
    Creature creature1;
    creature1.setHitpoints(10);
    creature1.setLevel(5);
    creature1.setTame(true);
    creature1.display();

    /**  
        2.2
            - Instantiate a creature with the parameterized constructor with the following creature details:
            Name: Wormy
            Category: MYSTICAL
            Level: 2
            Hitpoints: 3
            - Set Wormy as Tame with the appropriate setter function.

            - Print out the creature's information using the display() function:

            Expected output:
            WORMY
            Category: MYSTICAL
            Level: 2
            Hitpoints: 3
            Tame: TRUE
    */
    Creature creature2("Wormy", Creature::MYSTICAL, 3, 2, true);
    creature2.display();

    /*
    INCREMENTAL TESTING:

    // Test default constructor
    Creature defaultCreature;
    std::cout << "Default Creature Information:\n";
    defaultCreature.display();
    std::cout << std::endl;

    // Test setName function
    std::string name = "Daisy58";
    bool setNameResult = defaultCreature.setName(name);
    std::cout << "Set Name Result: " << (setNameResult ? "true" : "false") << "\n";
    std::cout << "Creature Name after setting: " << defaultCreature.getName() << "\n\n";

    // Test parameterized constructor
    Creature::Category category = Creature::MYSTICAL;
    Creature parameterizedCreature("Fluffy", category, 5, 8, true);
    std::cout << "Parameterized Creature Information:\n";
    parameterizedCreature.display();
    std::cout << std::endl;

    // Test setCategory function
    parameterizedCreature.setCategory(Creature::ALIEN);
    std::cout << "Creature Category after setting: " << parameterizedCreature.getCategory() << "\n\n";

    // Test setHitpoints function
    bool setHitpointsResult = parameterizedCreature.setHitpoints(15);
    std::cout << "Set Hitpoints Result: " << (setHitpointsResult ? "true" : "false") << "\n";
    std::cout << "Creature Hitpoints after setting: " << parameterizedCreature.getHitpoints() << "\n\n";

    // Test setLevel function
    bool setLevelResult = parameterizedCreature.setLevel(10);
    std::cout << "Set Level Result: " << (setLevelResult ? "true" : "false") << "\n";
    std::cout << "Creature Level after setting: " << parameterizedCreature.getLevel() << "\n\n";

    // Test setTame function
    parameterizedCreature.setTame(false);
    std::cout << "Creature Tame after setting: " << (parameterizedCreature.isTame() ? "TRUE" : "FALSE") << "\n\n";

    // Display final information for parameterizedCreature
    std::cout << "Final Parameterized Creature Information:\n";
    parameterizedCreature.display();
    */

    return 0;
}