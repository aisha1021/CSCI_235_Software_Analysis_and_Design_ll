/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 6  - Creature Training! 
*/

#include "Cavern.hpp"

int main() {
    Cavern cavern("creatures.csv");

    cavern.initializeAlienStack();
    cavern.initializeUndeadStack();
    cavern.initializeMysticalStack();
    cavern.initializeUnknownStack();

    std::stack<Creature*> alien_stack = cavern.getAlienStack();
    cavern.setAttacks(alien_stack);
    // std::stack<Creature*> undead_stack = cavern.getUndeadStack();
    // cavern.setAttacks(undead_stack);
    // std::stack<Creature*> mystical_stack = cavern.getMysticalStack();
    // cavern.setAttacks(mystical_stack);
    // std::stack<Creature*> unknown_stack = cavern.getUnknownStack();
    // cavern.setAttacks(unknown_stack);

    

    return 0;
}
