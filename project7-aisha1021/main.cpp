/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 7 - Binary Skill Tree
*/

#include "SkillTree.hpp"

int main() {
    auto test = SkillTree("debug.csv");
    test.preorderDisplay();
    test.removeSkill("skill2");
    std::cout << "\n" << "\n" << "\n" << "\n";
    test.preorderDisplay();

    return 0;
}