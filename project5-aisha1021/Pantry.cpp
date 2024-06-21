/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 5  - Ingredient Management with Linked Lists 
*/

#include "Pantry.hpp"

/**
    Default Constructor
*/
Pantry::Pantry() {}

/**
    @param: the name of an input file
    @pre: Formatting of the csv file is as follows:
        Name: A string
        Description: A string
        Quantity: A non negative integer
        Price: A non negative integer
        Recipe: A list of Ingredient titles of the form [NAME1] [NAME2];
        For example, to make this ingredient, you need (Ingredient 1 AND Ingredient 2)
        The value may be NONE.
    Notes:
        - The first line of the input file is a header and should be ignored.
        - The recipe are separated by a semicolon and may be NONE.
        - The recipe may be in any order.
        - If any of the recipe are not in the list, they should be created as new ingredients with the following information:
            - Title: The name of the ingredient
            - Description: "UNKNOWN"
            - Quantity: 0
            - Recipe: An empty vector
        - However, if you eventually encounter a ingredient that matches one of the "UNKNOWN" ingredients while parsing the file, you should update all the ingredient details.
        
        For example, given a row in the file:
        Inferno_Espresso,An energizing elixir brewed with mystical flames providing resistance to caffeine crashes for a limited time.,1,50,Fiery_Bean Ember_Spice

        The order of the ingredients in the list:
        Fiery_Bean, Ember_Spice, Inferno_Espresso
        Hint: update as needed using addIngredient()
        
    @post: Each line of the input file corresponds to a ingredient to be added to the list. No duplicates are allowed.
    Hint: use std::ifstream and getline()
*/
Pantry::Pantry(const std::string& inputFile) {
    std::ifstream file(inputFile);
    std::string line;

    std::getline(file, line); // skip the first line

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, description, recipeString;
        int quantity, price;
        std::vector<std::string> recipeNames;

        std::getline(ss, name, ','); // get name
        std::getline(ss, description, ','); // get description
        ss >> quantity; // get quantity
        ss.ignore(); // ignore comma
        ss >> price; // get price
        ss.ignore(); // ignore comma
        std::getline(ss, recipeString); // get recipe string

        std::stringstream recipeStream(recipeString); // parse recipe ingredients
        std::string ingredientName;
        while (std::getline(recipeStream, ingredientName, ' ')) {
            if (ingredientName.back() == '\r') {
                ingredientName.pop_back(); // remove return
                ingredientName.pop_back(); // remove return
                }
            else if (ingredientName.back() == ';') {
                ingredientName.pop_back(); // remove semicolon
            }
            recipeNames.push_back(ingredientName);
        }

        std::vector<Ingredient*> recipeIngredients; // create ingredient object
        for (const auto& ingredientName : recipeNames) {
            Ingredient* mainIngredient = nullptr;
            if (contains(ingredientName)) {
                mainIngredient = getPointerTo(getPosOf(ingredientName))->getItem();
            } else {
                mainIngredient = new Ingredient(ingredientName, "UNKNOWN", 0, 0, {}); // create a new ingredient with UNKNOWN details if not already in pantry
            }
            recipeIngredients.push_back(mainIngredient);
        }

        Ingredient* ingredient = new Ingredient(name, description, quantity, price, recipeIngredients); // create the main ingredient

        addIngredient(ingredient); // add the main ingredient to the pantry
    }
}

/**
    Destructor
    @post: Explicitly deletes every dynamically allocated Ingredient object
*/
Pantry::~Pantry() {
    for (int i = 0; i < getLength(); i++) { // loop through all items in the pantry
        delete getPointerTo(i)->getItem(); // delete the dynamically allocated memory for each ingredient
    }
}

/**
    @param: A const string reference to a ingredient name
    @return: The integer position of the given ingredient if it is in the Pantry, -1 if not found.
*/
int Pantry::getPosOf(const std::string& ingredientName) const {
    for (int i = 0; i < getLength(); i++) { // iterate through the pantry items
        if (getPointerTo(i) != nullptr && getPointerTo(i)->getItem()->name_ == ingredientName) { // check if the pointer to the item is not nullptr and the item's name matches the target ingredient name
            return static_cast<int>(i); // if found, return the index (position) of the ingredient
        }
    }
    return -1; // if the ingredient is not found, return -1
}

/**
    @param: A const string reference to a ingredient name
    @return: True if the ingredient information is already in the Pantry
*/
bool Pantry::contains(const std::string& ingredientName) const {
    return getPosOf(ingredientName) != -1; // check if the position of ingredient in the pantry is not equal to -1 (i.e., if the ingredient is found in the pantry)
}

/**
    @param:  A pointer to an Ingredient object
    @post:  Inserts the given ingredient pointer into the Pantry, unless an ingredient of the same name is already in the pantry. 
            Each of its Ingredients in its recipe are also added to the Pantry IF not already in the list.
    @return: True if the ingredient was added successfully, false otherwise.
*/
bool Pantry::addIngredient(Ingredient* ingredient) {
    if (!contains(ingredient->name_)) { // check if the ingredient is not already present in the pantry
        insert(getLength(), ingredient); // if the ingredient is not present, insert it into the pantry at the end
        return true; // return true if the addition was successful
    }
    return false; // otherwise, false
}

/**
    @param: A const string reference representing a ingredient name
    @param: A const string reference representing ingredient description
    @param: A const int reference representing the ingredient's quantity
    @param: A const int reference representing the ingredient's price
    @param: A const reference to a vector holding Ingredient pointers representing the ingredient's recipe
    @post:   Creates a new Ingredient object and inserts a pointer to it into the Pantry. 
            Each of its Ingredients in its recipe are also added to the Pantry IF not already in the list.
    @return: True if the ingredient was added successfully
*/
bool Pantry::addIngredient(const std::string& name, const std::string& description, int quantity, int price, const std::vector<Ingredient*>& recipe) {
    Ingredient* ingredient = new Ingredient(name, description, quantity, price, recipe); // create a new Ingredient object

    bool ingredientAdded = addIngredient(ingredient); // add the new ingredient to the pantry

    if (!ingredientAdded) { // if ingredient was not added, delete the dynamically allocated object
        delete ingredient;
        return false;
    }

    int recipeSize = recipe.size(); // add each ingredient in the recipe to the pantry if it's not already present
    for (int i = 0; i < recipeSize; i++) {
        if (!contains(recipe[i]->name_)) {
            addIngredient(recipe[i]);
        }
    }

    return true;
}

/**
    @param:  A Ingredient pointer
    @return: A boolean indicating if all the given ingredient can be created (all of the ingredients in its recipe can be created, or if you have enough of each ingredient in its recipe to create it)
*/
bool Pantry::canCreate(Ingredient* ingredient) const {
    if (ingredient->recipe_.empty()) { // if the ingredient has no recipe, it cannot be created
        return false;
    }

    for (int i = 0; i < ingredient->recipe_.size(); i++) { // check if all ingredients in the recipe are available in the pantry
        if (!contains(ingredient->recipe_[i]->name_)) { // if an ingredient in the recipe is not in the pantry
            if (!canCreate(ingredient->recipe_[i])) { // check if it's possible to create that ingredient recursively - if not, return false
                return false;
            }
        }
    }
    return true; // if all ingredients in the recipe are available in the pantry, return true
}

/**
    @param: A Ingredient pointer
    @post: Prints the ingredient name, quantity, and description.
    The output should be of the form:
    [Ingredient Name]: [Quantity]\n
    [Ingredient Description]\n
    Price: [Price]\n
    Recipe:\n
    [Ingredient0] [Ingredient1]\n


    If the ingredient has no recipe, print "Recipe:\nNONE\n\n" after the price.
*/
void Pantry::printIngredient(Ingredient* ingredient) const {
    std::cout << ingredient->name_ << ": " << ingredient->quantity_ << "\n"; // print the name and quantity of the ingredient
    std::cout << ingredient->description_ << "\n"; // print the description of the ingredient
    std::cout << "Price: " << ingredient->price_ << "\n"; // print the price of the ingredient
    
    if (ingredient->recipe_.empty()) { // check if the ingredient has a recipe
        std::cout << "Recipe:\nNONE\n\n"; // if no recipe, print NONE
    } else {
        std::cout << "Recipe:\n"; // if there's a recipe, print each ingredient in the recipe
        for (const auto& subIngredient : ingredient->recipe_) {
            std::cout << subIngredient->name_ << " ";
        }
        std::cout << "\n\n";
    }
}

/**
    @param: A const string reference to a ingredient name
    @post:  Prints a list of ingredients that must be created before the given ingredient can be created (missing ingredients for its recipe, where you have 0 of the needed ingredient).
            If the ingredient is already in the pantry, print "In the pantry([quantity])\n"
            If there are no instances of the ingredient, if it cannot be crafted because of insufficient ingredients, print "[Ingredient Name](0)\nMISSING INGREDIENTS"
            If it can be crafted, recursively print the ingredients that need to be used (if there are instances of them) or created (if there are no instances of them) in the order that the ingredients appear in the recipe, joined by "<-".
            If the ingredient has no recipe, print "UNCRAFTABLE\n" at the end of the function.

            Below are some of the expected forms. "Scenario: [scenario] is not part of the output. It is just to help you understand the expected output.":

            Scenario: The Ingredient does not exist in the list
            Query: [Ingredient Name]
            No such ingredient

            Scenario: The Ingredient exists in the list, and there are >0 instances of it
            Query: [Ingredient Name]
            In the pantry ([Quantity])

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is craftable by using an ingredient that is already in the pantry
            Query: [Ingredient Name0]
            [Ingredient Name0](C)
            [Ingredient Name1](1)

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is craftable by using an ingredient that has to be crafted
            Query: [Ingredient Name0]
            [Ingredient Name0](C)
            [Ingredient Name1](C) <- [Ingredient Name2](3)
            
            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and there are multiple ingredients that have to be crafted (each row represents a different ingredient inå the original recipe)
            Query: [Ingredient Name0]
            [Ingredient Name0](C)
            [Ingredient Name1](C) <- [Ingredient Name2](3)
            [Ingredient Name3](C) <- [Ingredient Name4](C) <- [Ingredient Name5] (3)

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is not craftable (it has no recipe)
            Query: [Ingredient Name0]
            UNCRAFTABLE

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it has a recipe, but you do not have enough of the ingredients to craft it
            Query: [Ingredient Name0]
            [Ingredient Name0](0)
            MISSING INGREDIENTS
    
    HINT: Use canCreate() to determine if the ingredient can be created.
*/
void Pantry::ingredientQuery(const std::string& ingredientName) const {\
    std::cout << "Query: " << ingredientName << std::endl;

    int position = getPosOf(ingredientName);
    if (position == -1) { // if the ingredient is not found, print message and return
        std::cout << "No such ingredient\n";
        return;
    }

    
    Ingredient* ingredient = getPointerTo(position)->getItem(); // retrieve the ingredient object from the pantry
    int quantity = ingredient->quantity_; // get the quantity of ingredient

    // check if the ingredient is in the pantry but uncraftable
    if ((quantity > 0 && ingredient->recipe_.empty()) || (quantity > 0 && ingredient->recipe_.size() == 1 && ingredient->recipe_[0]->name_ == "NONE")) {
        std::cout << "In the pantry (" << quantity << ")\n";
        std::cout << "UNCRAFTABLE\n";
        return;
    }

    
    if (quantity > 0) { // check if the ingredient is in the pantry
        std::cout << "In the pantry (" << quantity << ")\n";
        return;
    }

    // check if the ingredient is uncraftable due to missing ingredients
    if (ingredient->recipe_.empty() || (ingredient->recipe_.size() == 1 && ingredient->recipe_[0]->name_ == "NONE")) {
        std::cout << "UNCRAFTABLE\n";
        return;
    }

    bool hasMissingIngredients = false; // check if the ingredient can be crafted with the available ingredients
    for (const auto& recipeIngredient : ingredient->recipe_) {
        if (!contains(recipeIngredient->name_)) {
            hasMissingIngredients = true;
            break;
        }
    }

    if (!canCreate(ingredient)) { // if the ingredient cannot be crafted due to insufficient ingredients, print message and return
        std::cout << ingredientName << "(0)\n";
        std::cout << "MISSING INGREDIENTS\n";
        return;
    }

    std::cout << ingredientName << "(C)\n"; // if the ingredient can be crafted, print its name and recursively print its recipe
    printRecipe(ingredient);
    std::cout << "\n";
}

/**
    Prints the recipe of the given ingredient recursively. This is a helper function for ingredientQuery.

    @param ingredient A pointer to the Ingredient whose recipe is to be printed.
    @post Prints the recipe of the ingredient recursively.
*/
void Pantry::printRecipe(Ingredient* ingredient) const {
    for (int i = 0; i < ingredient->recipe_.size(); i++) { // loop through the recipe ingredients of the given ingredient
        if (!canCreate(getNodeAt(getPosOf(ingredient->recipe_[i]->name_))->getItem())) { // check if the current recipe ingredient cannot be created
            std::cout << ingredient->recipe_[i]->name_ << "(" << getNodeAt(getPosOf(ingredient->recipe_[i]->name_))->getItem()->quantity_ << ")" << std::endl; // print the name and quantity of the recipe ingredient
        } else {
            std::cout << ingredient->recipe_[i]->name_ << "(C)"; // if the recipe ingredient can be created, print name and "(C)" to indicate it is craftable
            std::cout << " <- ";
            printRecipe(getNodeAt(getPosOf(ingredient->recipe_[i]->name_))->getItem()); // recursively call printRecipe to print the recipe of the current recipe ingredient
        }
    }
}

/**
    @return: An integer sum of the price of all the ingredients currently in the list.
    Note: This should only include price values from ingredients that you have 1 or more of. Do not consider ingredients that you have 0 of, even if you have the ingredients to make them.
*/
int Pantry::calculatePantryValue() const {
    int totalValue = 0; // initialize total value counter

    for (int i = 0; i < getLength(); i++) { // tierate through all items in the pantry
        Ingredient* ingredient = getPointerTo(i)->getItem(); // get pointer to the ingredient
        if (ingredient->quantity_ > 0) { // check if the ingredient is present in the pantry
            totalValue += ingredient->price_ * ingredient->quantity_; // if the quantity is greater than 0, calculate the value and add to the total
        }
    }
    return totalValue; // return the total value of all ingredients in the pantry
}

/**
    @param: A const string reference to a filter with a default value of "NONE".
    @post: With default filter "NONE": Print out every ingredient in the list.
        With filter "CONTAINS":   Only print out the ingredients with >0 instances in the list.
        With filter "MISSING": Only print out the ingredients with 0 instances in the list.
        With filter "CRAFTABLE":  Only print out the ingredients where you have all the ingredients to craft them.
        If an invalid filter is passed, print "INVALID FILTER\n"
        Printing ingredients should be of the form:

        [Ingredient name]: [Quantity]
        [Ingredient description]\n
        Price: [price]\n
        Recipe:\n
        [Ingredient0] [Ingredient1]\n\n

        If the ingredient has no recipe, print "Recipe:\nNONE\n\n" after the price.
*/
void Pantry::pantryList(const std::string& filter) const {
    if (filter == "NONE") { // check the filter type
        for (int i = 0; i < getLength(); i++) { // print all ingredients regardless of quantity
            Ingredient* ingredient = getPointerTo(i)->getItem();
            std::cout << ingredient->name_ << ": " << ingredient->quantity_ << "\n"; // print ingredient details
            std::cout << ingredient->description_ << "\n";
            std::cout << "Price: " << ingredient->price_ << "\n";
            if (ingredient->recipe_.empty()) { // print recipe
                std::cout << "Recipe:\nNONE\n\n";
            } else {
                std::cout << "Recipe:\n";
                for (const auto& subIngredient : ingredient->recipe_) {
                    std::cout << subIngredient->name_ << " ";
                }
                std::cout << "\n\n";
            }
        }
    } else if (filter == "CONTAINS") {
        for (int i = 0; i < getLength(); i++) { // print ingredients with quantity greater than 0
            Ingredient* ingredient = getPointerTo(i)->getItem();
            if (ingredient->quantity_ > 0) {
                std::cout << ingredient->name_ << ": " << ingredient->quantity_ << "\n"; // print ingredient details
                std::cout << ingredient->description_ << "\n";
                std::cout << "Price: " << ingredient->price_ << "\n";
                if (ingredient->recipe_.empty()) { // print recipe
                    std::cout << "Recipe:\nNONE\n\n";
                } else {
                    std::cout << "Recipe:\n";
                    for (const auto& subIngredient : ingredient->recipe_) {
                        std::cout << subIngredient->name_ << " ";
                    }
                    std::cout << "\n\n";
                }
            }
        }
    } else if (filter == "MISSING") {
        for (int i = 0; i < getLength(); i++) { // print ingredients with quantity equal to 0
            Ingredient* ingredient = getPointerTo(i)->getItem();
            if (ingredient->quantity_ == 0) {
                std::cout << ingredient->name_ << ": " << ingredient->quantity_ << "\n"; // print ingredient details
                std::cout << ingredient->description_ << "\n";
                std::cout << "Price: " << ingredient->price_ << "\n";
                if (ingredient->recipe_.empty()) { // print recipe
                    std::cout << "Recipe:\nNONE\n\n";
                } else {
                    std::cout << "Recipe:\n";
                    for (const auto& subIngredient : ingredient->recipe_) {
                        std::cout << subIngredient->name_ << " ";
                    }
                    std::cout << "\n\n";
                }
            }
        }
    } else if (filter == "CRAFTABLE") {
        for (int i = 0; i < getLength(); i++) { // print craftable ingredients
            Ingredient* ingredient = getPointerTo(i)->getItem();
            if (canCreate(ingredient)) {
                std::cout << ingredient->name_ << ": " << ingredient->quantity_ << "\n"; // print ingredient details
                std::cout << ingredient->description_ << "\n";
                std::cout << "Price: " << ingredient->price_ << "\n";
                if (ingredient->recipe_.empty()) { // print recipe
                    std::cout << "Recipe:\nNONE\n\n";
                } else {
                    std::cout << "Recipe:\n";
                    for (const auto& subIngredient : ingredient->recipe_) {
                        std::cout << subIngredient->name_ << " ";
                    }
                    std::cout << "\n\n";
                }
            }
        }
    } else {
        std::cout << "INVALID FILTER\n"; // invalid filter type
    }
}