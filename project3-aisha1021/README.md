# Algorithmic Adventures II: The Exponential Creature Odyssey

## Project 2 - Creature Types: Inheritance

### Overview

In this project, you will define and implement different types of Creatures by creating three new classes derived from the `Creature` class. These new classes will have additional attributes and methods specific to their type:

- **Dragons** are majestic and powerful creatures with a strong connection to elemental forces. Each Dragon may have an affinity to a specific element, a number of heads, and the ability to fly.
- **Ghouls** are nightmarish creatures that feed on the living. Each Ghoul has a level of decay, belongs to a faction, and may have a transformation ability.
- **Mindflayers** are otherworldly beings with powerful psionic abilities. Each Mindflayer has a limited source of ammunition, which comes in different types of psychic projectiles. They may also summon a Thoughtspawn and have a list of affinities that enhance their projectile damage.

### Assignment

To accept the GitHub Classroom assignment, please find the link on Blackboard.

### Additional Resources

- **Inheritance:**
  - [Code Beauty](https://www.codebeauty.com/inheritance-programming)
  - [Caleb Curry](https://www.calebcurry.com/base-and-subclass-inheritance)
- **Enums and Structs:**
  - [Enums](https://www.geeksforgeeks.org/enumeration-enum-c/)
  - [Structs](https://www.geeksforgeeks.org/structures-c/)

### Implementation

Work through the tasks sequentially (implement and test). Only move on to a task when you are positive that the previous one has been completed correctly. Ensure that the names of classes and methods exactly match those in this specification.

**Important:** You must thoroughly document your code!

### Task 1: Subclasses

#### The Dragon Class

##### Data Types

The Dragon class must define the following type publicly inside the class:
```cpp
enum Element {NONE, FIRE, WATER, EARTH, AIR};
```

##### Private Member Variables

- An `Element` representing their affinity.
- An integer representing the number of heads.
- A boolean indicating if they can fly.

##### Constructors

```cpp
/**
  Default constructor.
  Default-initializes all private members. 
  Default Category: MYSTICAL
  Default element: NONE
  Default number of heads: 1
  Booleans are default-initialized to False. 
*/

/**
  Parameterized constructor.
  @param      : The name of the Dragon (a reference to string)
  @param      : The category of the Dragon (a Category enum) with default value MYSTICAL
  @param      : The Dragon's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : The Dragon's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : A flag indicating whether the Dragon is tame, with default value False
  @param      : The element (an Element enum), with default value NONE if not provided
  @param      : The number of heads (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : A flag indicating whether the Dragon can fly, with default value False
  @post       : The private members are set to the values of the corresponding parameters.
  Hint: Notice the default arguments in the parameterized constructor.
*/
```

##### Unique Methods

```cpp
/**
  Getter for the element.
  @return     : The element (a string representation of the Element enum)
*/
std::string getElement() const;

/**
  Setter for the element.
  @param      : A reference to the element (an Element enum)
  @post       : The element is set to the value of the parameter.
*/
void setElement(Element element);

/**
  Getter for the number of heads.
  @return     : The number of heads (an integer)
*/
int getNumberOfHeads() const;

/**
  Setter for the number of heads.
  @param      : A reference to the number of heads (an integer)
  @pre        : The number of heads is > 0. Do nothing for invalid values.
  @post       : The number of heads is set to the value of the parameter.
  @return     : True if the number of heads is set, false otherwise.
*/
bool setNumberOfHeads(int heads);

/**
  Getter for the flight flag.
  @return     : The flight flag (a boolean)
*/
bool getFlight() const;

/**
  Setter for the flight flag.
  @param      : A reference to the flight flag (a boolean)
  @post       : The flight flag is set to the value of the parameter.
*/
void setFlight(bool canFly);
```

#### The Ghoul Class

##### Data Types

The Ghoul class must define the following type publicly inside the class:
```cpp
enum Faction {NONE, FLESHGORGER, SHADOWSTALKER, PLAGUEWEAVER};
```

##### Private Member Variables

- An integer representing their level of decay.
- A `Faction` representing their faction.
- A boolean indicating if they can transform.

##### Constructors

```cpp
/**
  Default constructor.
  Default-initializes all private members. 
  Default Category: UNDEAD
  Default decay: 0
  Default faction: NONE
  Booleans are default-initialized to False. 
*/

/**
  Parameterized constructor.
  @param      : The name of the Ghoul (a reference to string)
  @param      : The category of the Ghoul (a Category enum) with default value UNDEAD
  @param      : The Ghoul's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : The Ghoul's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : A flag indicating whether the Ghoul is tame, with default value False
  @param      : The level of decay (an integer), with default value 0 if not provided, or if the value provided is negative
  @param      : The faction (a Faction enum), with default value NONE if not provided
  @param      : A flag indicating whether the Ghoul can transform, with default value False
  @post       : The private members are set to the values of the corresponding parameters.
  Hint: Notice the default arguments in the parameterized constructor.
*/
```

##### Unique Methods

```cpp
/**
  Getter for the level of decay.
  @return     : The level of decay (an integer)
*/
int getDecay() const;

/**
  Setter for the level of decay.
  @param      : A reference to the level of decay (an integer)
  @pre        : The level of decay must be >= 0 (do nothing otherwise)
  @post       : The level of decay is set to the value of the parameter.
  @return     : True if the level of decay was set, false otherwise.
*/
bool setDecay(int decay);

/**
  Getter for the faction.
  @return     : The faction (a string representation of the Faction enum)
*/
std::string getFaction() const;

/**
  Setter for the faction.
  @param      : A reference to the faction (a Faction enum)
  @post       : The faction is set to the value of the parameter.
*/
void setFaction(Faction faction);

/**
  Getter for the transformation.
  @return     : The transformation (a boolean)
*/
bool getTransformation() const;

/**
  Setter for the transformation.
  @param      : A reference to the transformation (a boolean)
  @post       : The transformation is set to the value of the parameter.
*/
void setTransformation(bool canTransform);
```

#### The Mindflayer Class

##### Data Types

The Mindflayer class must define the following types publicly inside the class:
```cpp
enum Variant {PSIONIC, TELEPATHIC, ILLUSIONARY};

struct Projectile {
    Variant type_;
    int quantity_;
};
```

##### Private Member Variables

- A vector of `Projectile` structs.
- A vector of `Variant` enums representing their affinities.
- A boolean indicating if they can summon a Thoughtspawn.

##### Constructors

```cpp
/**
  Default constructor.
  Default-initializes all private members. 
  Default Category: ALIEN
  Default summoning: False
*/

/**
  Parameterized constructor.
  @param      : A reference to the name of the Mindflayer (a string)
  @param      : The category of the Mindflayer (a Category enum) with default value ALIEN
  @param      : The Mindflayer's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : The Mindflayer's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : A flag indicating whether the Mindflayer is tame, with default value False
  @param      : The projectiles (a vector of Projectile structs), with default value an empty vector if not provided
  @param      : A flag indicating whether the Mindflayer can summon, with default value False
  @param      : The affinities (a vector of Variant enums), with default value an empty vector if not provided
  @post       : The private members are set to the values of the

 corresponding parameters.
  Hint: Notice the default arguments in the parameterized constructor.
*/
```

##### Unique Methods

```cpp
/**
  Getter for the projectiles.
  @return     : The projectiles (a vector of Projectile structs)
*/
std::vector<Projectile> getProjectiles() const;

/**
  Setter for the projectiles.
  @param      : A reference to the projectiles (a vector of Projectile structs)
  @post       : The projectiles are set to the value of the parameter. There should not be any duplicate projectiles in the Mindflayer's projectiles vector.
                For example, if the vector in the given parameter contains the following Projectiles: {{PSIONIC, 2}, {TELEPATHIC, 1}, {PSIONIC, 1}, {ILLUSIONARY, 3}}, 
                the projectiles vector should be set to contain the following Projectiles: {{PSIONIC, 3}, {TELEPATHIC, 1}, {ILLUSIONARY, 3}}.
                If the quantity of a projectile is 0 or negative, it should not be added to the projectiles vector. 
                Note the order of the projectiles in the vector.
*/
void setProjectiles(const std::vector<Projectile>& projectiles);

/**
  Getter for the summoning.
  @return     : The summoning (a boolean)
*/
bool getSummoning() const;

/**
  Setter for the summoning.
  @param      : A reference to the summoning (a boolean)
  @post       : The summoning is set to the value of the parameter.
*/
void setSummoning(bool canSummon);

/**
  Getter for the affinities.
  @return     : The affinities (a vector of Variant enums)
*/
std::vector<Variant> getAffinities() const;

/**
  Setter for the affinities.
  @param      : A reference to the affinities (a vector of Variant enums)
  @post       : The affinities are set to the value of the parameter.
                There should not be any duplicate affinities in the Mindflayer's affinities vector. 
                For example, if the vector in the given parameter contains the following affinities: {PSIONIC, TELEPATHIC, PSIONIC, ILLUSIONARY}, 
                the affinities vector should be set to contain the following affinities: {PSIONIC, TELEPATHIC, ILLUSIONARY}.
                Note the order of the affinities in the vector.
*/
void setAffinities(const std::vector<Variant>& affinities);

/**
  @param       : A reference to the Variant 
  @return      : The string representation of the variant
*/
std::string variantToString(const Variant& variant) const;
```

### Task 2: Testing

To give you some guidance on testing, we have added a testing task to this project. However, this task is not a thorough test of your classes. You must test every function you implement with valid and invalid values to ensure it behaves as specified. This is intended to motivate you to build a methodical and incremental testing practice.

Write a testing program as described below and name the file `test.cpp`.

#### Test Cases

For each creature object, print out the creature's information, including private member variables unique to their subclass, using the appropriate getter functions in the specified format.

##### Dragons

**Format:**
```
NAME: [NAME]
CATEGORY: [CATEGORY]
HP: [HITPOINTS]
LVL: [LEVEL]
TAME: [TAME]
ELEMENT: [ELEMENT]
HEADS: [NUMBER OF HEADS]
FLIGHT: [FLIGHT]
```

1. Instantiate a default Dragon and print its information.
2. Instantiate a Dragon named Smog using the parameterized constructor and print its information.
3. Instantiate a Dragon named BURNY with specific details and print its information.
4. Modify BURNY using setter functions and print its information.

##### Ghouls

**Format:**
```
NAME: [NAME]
CATEGORY: [CATEGORY]
HP: [HITPOINTS]
LVL: [LEVEL]
TAME: [TAME]
DECAY: [DECAY]
FACTION: [FACTION]
TRANSFORM: [TRANSFORM]
```

1. Instantiate a default Ghoul and print its information.
2. Instantiate a Ghoul named Homph using the parameterized constructor and print its information.
3. Instantiate a Ghoul named CHOMPER with specific details and print its information.
4. Modify CHOMPER using setter functions and print its information.

##### Mindflayers

**Format:**
```
NAME: [NAME]
CATEGORY: [CATEGORY]
HP: [HITPOINTS]
LVL: [LEVEL]
TAME: [TAME]
SUMMONING: [SUMMONING]
[PROJECTILE TYPE 1]: [QUANTITY 1]
[PROJECTILE TYPE 2]: [QUANTITY 2]
AFFINITIES:
[AFFINITY 1]
[AFFINITY 2]
```

1. Instantiate a default Mindflayer and print its information.
2. Instantiate a Mindflayer named BIGBRAIN with specific details and print its information.

### Compiling with Makefile

To compile with your Makefile, use the following command in the terminal, in the same directory as your Makefile and your source files:

```bash
make rebuild
```

This assumes you did not rename the Makefile and that it is the only one in the current directory.

### Incremental Implementation and Testing

Implement and test your programs incrementally. For each class:

- Implement one function/method and test it thoroughly.
- Only when you are certain that function works correctly and matches the specification, move on to the next.
- Write your own `main()` function to test your classes.
- Thoroughly test with valid and invalid input to check that your function behaves as expected in each case, paying special attention to edge cases.
- If you need to use a function you have not yet implemented, use stubs and ensure to replace them with actual implementations later.

### Grading Rubric

- **Correctness:** 80% (distributed across unit testing of your submission)
- **Documentation:** 15%
- **Style and Design:** 5% (proper naming, modularity, and organization)

**Important:** Start working on the projects as soon as they are assigned to detect any problems and address them with us well before the deadline.

### Submission

Submit the following files:
- `Dragon.hpp`
- `Dragon.cpp`
- `Mindflayer.hpp`
- `Mindflayer.cpp`
- `Ghoul.hpp`
- `Ghoul.cpp`
- `test.cpp`

Although Gradescope allows multiple submissions, it is not a platform for testing and debugging. You MUST test and debug your program locally. To help you not rely too much on Gradescope for testing, we will only allow 5 submissions per day. Before submitting to Gradescope, ensure that your program compiles using the provided Makefile and runs correctly on the Linux machines in the labs at Hunter. This is your baseline; if it runs correctly there, it will run correctly on Gradescope. If not, you will have the necessary feedback to guide you in debugging.

**Due date:** This project is due on 2/19. No late submissions will be accepted.

### Help

Help is available via drop-in tutoring in Lab 1001B (see the website for the schedule). Start early to ensure you get the help you need.

### Authors

- Georgina Woo
- Tiziana Ligorio
```
