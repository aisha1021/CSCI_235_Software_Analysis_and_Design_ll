/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 2 - Creature Types: Inheritance
*/

#include "Creature.hpp"
#include "Dragon.hpp"
#include "Ghoul.hpp"
#include "Mindflayer.hpp"

/**
    Prints the information of the given Dragon object.
    @param dragon: A reference to the Dragon object to print information for.
    @post Outputs the following information about the Dragon:
        - NAME
        - CATEGORY
        - HP
        - LVL
        - TAME
        - ELEMENT
        - HEADS
        - FLIGHT
*/
void printDragonInfo(const Dragon& dragon) {
    std::cout << "NAME: " << dragon.getName() << "\n"
              << "CATEGORY: " << dragon.getCategory() << "\n"
              << "HP: " << dragon.getHitpoints() << "\n"
              << "LVL: " << dragon.getLevel() << "\n"
              << "TAME: " << (dragon.isTame() ? "TRUE" : "FALSE") << "\n"
              << "ELEMENT: " << dragon.getElement() << "\n"
              << "HEADS: " << dragon.getNumberOfHeads() << "\n"
              << "FLIGHT: " << (dragon.getFlight() ? "TRUE" : "FALSE") << "\n";
}

/**
    Prints the information of the given Ghoul object.
    @param ghoul: A reference to the Ghoul object to print information for.
    @post Outputs the following information about the Ghoul:
        - NAME
        - CATEGORY
        - HP
        - LVL
        - TAME
        - DECAY
        - FACTION
        - TRANSFORM
*/
void printGhoulInfo(const Ghoul& ghoul) {
    std::cout << "NAME: " << ghoul.getName() << "\n"
              << "CATEGORY: " << ghoul.getCategory() << "\n"
              << "HP: " << ghoul.getHitpoints() << "\n"
              << "LVL: " << ghoul.getLevel() << "\n"
              << "TAME: " << (ghoul.isTame() ? "TRUE" : "FALSE") << "\n"
              << "DECAY: " << ghoul.getDecay() << "\n"
              << "FACTION: " << ghoul.getFaction() << "\n"
              << "TRANSFORM: " << (ghoul.getTransformation() ? "TRUE" : "FALSE") << "\n";
}

/**
    Prints the information of the given Mindflayer object.
    @param mindflayer: A reference to the Mindflayer object to print information for.
    @post Outputs the following information about the Mindflayer:
        - NAME
        - CATEGORY
        - HP
        - LVL
        - TAME
        - SUMMONING
        - PROJECTILES (if any)
        - AFFINITIES (if any)
*/
void printMindflayerInfo(const Mindflayer& mindflayer) {
    std::cout << "NAME: " << mindflayer.getName() << "\n"
              << "CATEGORY: " << mindflayer.getCategory() << "\n"
              << "HP: " << mindflayer.getHitpoints() << "\n"
              << "LVL: " << mindflayer.getLevel() << "\n"
              << "TAME: " << (mindflayer.isTame() ? "TRUE" : "FALSE") << "\n"
              << "SUMMONING: " << (mindflayer.getSummoning() ? "TRUE" : "FALSE") << "\n";

    auto projectiles = mindflayer.getProjectiles();
    if (!projectiles.empty()) {
        for (const auto& projectile : projectiles) {
            std::cout << mindflayer.variantToString(projectile.type_) << ": " << projectile.quantity_ << "\n";
        }
    }

    auto affinities = mindflayer.getAffinities();
    if (!affinities.empty()) {
        std::cout << "AFFINITIES: \n";
        for (const auto& affinity : affinities) {
            std::cout << mindflayer.variantToString(affinity) << "\n";
        }
    }
}

int main() {
    /*
        2.1.1 Instantiate a default Dragon
        
        NAME: [NAME]\n
        CATEGORY: [CATEGORY]\n
        HP: [HITPOINTS]\n
        LVL: [LEVEL]\n
        TAME: [TAME]\n
        ELEMENT: [ELEMENT]\n
        HEADS: [NUMBER OF HEADS]\n
        FLIGHT: [FLIGHT]\n

        - Print out the information for the default Dragon based on the format above
    */
    Dragon defaultDragon;
    printDragonInfo(defaultDragon);
    std::cout << "\n";

    /*
        2.1.2 Instantiate a Dragon with the parameterized constructor with the following creature details:
        Name: Smog

        - Print out the information for Smog based on the format above
    */
    Dragon smog("Smog");
    printDragonInfo(smog);
    std::cout << "\n";

    /*
        2.1.3 Instantiate a Dragon with the parameterized constructor with the following creature details:
        
        Name: BURNY
        Category: UNDEAD
        Hitpoints: 100
        Level: 10
        Tame: True
        Element: FIRE
        Number of heads: 1
        Flight: True

        - Print out the information for Burny based on the format above
    */
    Dragon burny("BURNY", Creature::UNDEAD, 100, 10, true, Dragon::FIRE, 1, true);
    printDragonInfo(burny);
    std::cout << "\n";

    /*
        2.1.4 Make the following changes to Burny using the appropriate setter functions:
        - Set the element to WATER
        - Set the number of heads to 2
        - Set the number of heads to 0
        - Set the flight flag to False

        - Print out the information for Burny based on the format above
    */
    burny.setElement(Dragon::WATER);
    burny.setNumberOfHeads(2);
    burny.setFlight(false);
    printDragonInfo(burny);
    std::cout << "\n";

    /*
        2.2.1 Instantiate a default Ghoul

        NAME: [NAME]\n
        CATEGORY: [CATEGORY]\n
        HP: [HITPOINTS]\n
        LVL: [LEVEL]\n
        TAME: [TAME]\n
        DECAY: [DECAY]\n
        FACTION: [FACTION]\n
        TRANSFORM: [TRANSFORM]\n
        
        - Print out the information for the default Ghoul based on the format above
    */
    Ghoul defaultGhoul;
    printGhoulInfo(defaultGhoul);
    std::cout << "\n";

    /*
        2.2.2 Instantiate a Ghoul with the parameterized constructor with the following creature details:
        Name: Homph

        - Print out the information for Homph based on the format above
    */
    Ghoul homph("Homph");
    printGhoulInfo(homph);
    std::cout << "\n";

    /*
        2.2.3 Instantiate a Ghoul with the parameterized constructor with the following creature details:
        Name: CHOMPER
        Category: ALIEN
        Hitpoints: 100
        Level: 10
        Tame: True
        Decay: 3
        Faction: FLESHGORGER
        Transform: True

        - Print out the information for Chomper based on the format above
    */
    Ghoul chomper("CHOMPER", Creature::ALIEN, 100, 10, true, 3, Ghoul::FLESHGORGER, true);
    printGhoulInfo(chomper);
    std::cout << "\n";

    /*
        2.2.4 Make the following changes to Chomper using the appropriate setter functions:
        - Set the decay to 2
        - Set the decay to -20
        - Set the faction to SHADOWSTALKER
        - Set the transformation flag to False

        - Print out the information for Chomper based on the format above
    */
    chomper.setDecay(2);
    chomper.setDecay(-20);
    chomper.setFaction(Ghoul::SHADOWSTALKER);
    chomper.setTransformation(false);
    printGhoulInfo(chomper);
    std::cout << "\n";

    /*
        2.3.1 Instantiate a default Mindflayer

        NAME: [NAME]\n
        CATEGORY: [CATEGORY]\n
        HP: [HITPOINTS]\n
        LVL: [LEVEL]\n
        TAME: [TAME]\n
        SUMMONING: [SUMMONING]\n
        [PROJECTILE TYPE 1]: [QUANTITY 1]\n
        [PROJECTILE TYPE 2]: [QUANTITY 2]\n
        AFFINITIES: \n
        [AFFINITY 1]\n
        [AFFINITY 2]\n

        - Print out the information for the default Mindflayer based on the format above
    */
    Mindflayer defaultMindflayer;
    printMindflayerInfo(defaultMindflayer);
    std::cout << "\n";

    /*
        2.3.2 Instantiate a Mindflayer with the parameterized constructor with the following creature details:

        Name: BIGBRAIN
        Category: MYSTICAL
        Hitpoints: 100
        Level: 10
        Tame: True
        Projectiles: {{PSIONIC, 2}, {TELEPATHIC, 1}, {PSIONIC, 1}, {ILLUSIONARY, 3}}
        Summoning: True
        Affinities: {PSIONIC, TELEPATHIC, PSIONIC, ILLUSIONARY}

        - Print out the information for Bigbrain based on the format above
    */
    std::vector<Mindflayer::Projectile> bigbrainProjectiles = {
        {Mindflayer::PSIONIC, 2},
        {Mindflayer::TELEPATHIC, 1},
        {Mindflayer::PSIONIC, 1},
        {Mindflayer::ILLUSIONARY, 3}
    };
    std::vector<Mindflayer::Variant> bigbrainAffinities = {Mindflayer::PSIONIC, Mindflayer::TELEPATHIC, Mindflayer::PSIONIC, Mindflayer::ILLUSIONARY};
    Mindflayer bigbrain("BIGBRAIN", Creature::MYSTICAL, 100, 10, true, bigbrainProjectiles, true, bigbrainAffinities);
    printMindflayerInfo(bigbrain);
    std::cout << "\n";

    return 0;
}
