/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 3 - The Cavern
*/

#include <iostream>
#include "Creature.hpp"
#include "Cavern.hpp"

int main() {
    Creature Kenjaku("Kenjaku", Creature::Category::UNKNOWN, 1, 9, false);
    Creature Gojo("Gojo", Creature::Category::UNDEAD, 1, 10, true);
    Creature Mechamaru("Mechamaru", Creature::Category::UNDEAD, 1, 7, true);
    Creature Nanami("Nanami", Creature::Category::UNDEAD, 1, 4, true);
    Creature Yuji("Yuji", Creature::Category::MYSTICAL, 1, 10, true);
    Creature Sukuna("Sukuna", Creature::Category::MYSTICAL, 1, 10, false);
    Creature Mahoraga("Mahoraga", Creature::Category::ALIEN, 1, 9, false);

    Cavern cavern;
    cavern.enterCavern(Kenjaku);
    cavern.enterCavern(Gojo);
    cavern.enterCavern(Mechamaru);
    cavern.enterCavern(Nanami);
    cavern.enterCavern(Yuji);
    cavern.enterCavern(Sukuna);
    cavern.enterCavern(Mahoraga);

    cavern.cavernReport();

    return 0;
}
