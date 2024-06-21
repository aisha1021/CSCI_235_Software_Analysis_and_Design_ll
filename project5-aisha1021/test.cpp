#include "Pantry.hpp"
#include <iostream>

int main() {
    Pantry pantry("debug.csv");

    // pantry.pantryList("NONE");

    pantry.ingredientQuery("in1");
    std::cout << std::endl;
    pantry.ingredientQuery("in2");
    std::cout << std::endl;
    pantry.ingredientQuery("in3");
    std::cout << std::endl;
    pantry.ingredientQuery("in4");
    std::cout << std::endl;
    pantry.ingredientQuery("in5");
    std::cout << std::endl;
    pantry.ingredientQuery("in6");
    std::cout << std::endl;
    pantry.ingredientQuery("in7");
    std::cout << std::endl;
    pantry.ingredientQuery("in8");

    return 0;
}
