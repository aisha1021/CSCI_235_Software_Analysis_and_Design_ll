# Algorithmic Adventures II: The Exponential Creature Odyssey

## Project 1 - The Creature Class: A Review of OOP

### Overview
This project aims to develop a Creature-world simulation, introducing participants to GitHub Classroom and refreshing their Object-Oriented Programming (OOP) skills by implementing the `Creature` class. The simulation involves capturing and taming mythical creatures categorized as Undead, Mystical, or Alien.

### Part 1 - Getting Started with GitHub Classroom
1. **Create a GitHub Account**: [Sign up for GitHub](https://github.com).
2. **Learn Git Basics**: Watch this [GitHub basics video](https://www.youtube.com/watch?v=MJUJ4wbFm_A).
3. **GitHub Classroom Tutorial**: Watch this [GitHub Classroom video](https://www.youtube.com/watch?v=AHDCokfgcSo).

### Additional Resources for OOP
- [Code Beauty on constructors and class methods](https://youtu.be)
- [thenewboston on classes and objects](https://youtu.be)
- [McProgramming on .hpp and .cpp files](https://youtu.be)

### Documentation Requirements
All projects must include thorough documentation:
- File preamble with name, date, and description.
- Function preambles with `@pre`, `@param`, `@return`, and `@post` where applicable.
- Inline comments for non-trivial functions.

### Part 2 - The `Creature` Class
Implement the `Creature` class with the following specifications:

#### Enum
- `Category` with values {UNKNOWN, UNDEAD, MYSTICAL, ALIEN}

#### Private Member Variables
- `name_` (string, uppercase)
- `category_` (enum)
- `hitpoints_` (integer)
- `level_` (integer)
- `tame_` (boolean)

#### Public Member Functions

##### Constructors
- **Default Constructor**: Initializes default values.
- **Parameterized Constructor**: Sets values based on parameters, with default and validation rules.

##### Accessors and Mutators
- `setName`
- `getName`
- `setCategory`
- `getCategory`
- `setHitpoints`
- `getHitpoints`
- `setLevel`
- `getLevel`
- `setTame`
- `isTame`
- `display`

### Task 1: The Creature Class

#### UML
Every Creature has a Name, Category, Hitpoints, Level, and a boolean if the creature is Tame. The Creature class must define the following type INSIDE the class definition:

- An enum named `Category` with values {UNKNOWN, UNDEAD, MYSTICAL, ALIEN}

#### Private Member Variables
- The name of the creature (a string in UPPERCASE)
- The category of the creature (an enum)
- The creature's hitpoints (an integer)
- The creature's level (an integer)
- A boolean flag indicating whether the creature is tame

#### Public Member Functions

##### Constructors
- **Default Constructor**
```cpp
/**
  Default constructor.
  Default-initializes all private members.
  Default creature name: "NAMELESS".
  Booleans are default-initialized to False.
  Default enum value: UNKNOWN
  Default Hitpoints and Level: 1.
 */
```
- **Parameterized Constructor**
```cpp
/**
  Parameterized constructor.
  @param: A reference to the name of the creature (a string). Set the creature's name to NAMELESS if the provided string contains non-alphabetic characters.
  @param: The category of the creature (a Category enum) with default value UNKNOWN
  @param: The creature's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param: The creature's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param: A flag indicating whether the creature is tame, with default value False
  @post: The private members are set to the values of the corresponding parameters. The name is converted to UPPERCASE if it consists of alphabetical characters only, otherwise it is set to NAMELESS.
 */
```

##### Accessors and Mutators

- **setName**
```cpp
/**
  @param: the name of the Creature, a reference to string
  @post: sets the Creature's name to the value of the parameter in UPPERCASE.
         (convert any lowercase character to uppercase)
         Only alphabetical characters are allowed.
       : If the input contains non-alphabetic characters, do nothing.
  @return: true if the name was set, false otherwise
 */
```
- **getName**
```cpp
/**
  @return: the name of the Creature
 */
```
- **setCategory**
```cpp
/**
  @param: a reference to Category, the category of the Creature (an enum)
  @post: sets the Creature's category to the value of the parameter
        : If the given category was invalid, set category_ to UNKNOWN.
 */
```
- **getCategory**
```cpp
/**
  @return: the category of the Creature (in string form)
 */
```
- **setHitpoints**
```cpp
/**
  @param: a reference to integer that represents the creature's hitpoints
  @pre: hitpoints >= 0 : Characters cannot have negative hitpoints
        (do nothing for invalid input)
  @post: sets the hitpoints private member to the value of the parameter
  @return: true if the hitpoints were set, false otherwise
 */
```
- **getHitpoints**
```cpp
/**
  @return: the value stored in hitpoints_
 */
```
- **setLevel**
```cpp
/**
  @param: a reference to integer level
  @pre: level >= 0 : Characters cannot have a negative level
  @post: sets the level private member to the value of the parameter
         (do nothing for invalid input)
  @return: true if the level was set, false otherwise
 */
```
- **getLevel**
```cpp
/**
  @return: the value stored in level_
 */
```
- **setTame**
```cpp
/**
  @param: a reference to boolean value
  @post: sets the tame flag to the value of the parameter
 */
```
- **isTame**
```cpp
/**
  @return: true if the creature is tame, false otherwise
  Note: this is an accessor function and must follow the same convention as all accessor functions even if it is not called getTame
 */
```
- **display**
```cpp
/**
  @post: displays Creature data in the form:
        "[NAME]\n
         Category: [CATEGORY]\n
         Level: [LEVEL]\n
         Hitpoints: [Hitpoints]\n
         Tame: [TRUE/FALSE]"
 */
```

### Task 2: Testing
Submit `test.cpp` with:
- Test cases for both default and parameterized constructors.
- Use `set` functions to modify attributes.
- Use `display()` to verify output.

#### Testing Instructions
To help you establish a good practice for testing, we will make the testing of your code part of the assignment. After the first few projects, this will simply be your regular development practice (thoroughly test every function you implement before moving to the next function), and we will no longer request  that you submit a test file.

If you want to submit to Gradescope before completing this test file, you can simply submit an empty main function, or a partially implemented function. Comment out any untested or buggy code.

Submit a file called `test.cpp` that includes only a main function that does the following:

##### Task 2.1
- Instantiate a creature with the default constructor
- Set its hitpoints to 10 using the appropriate setter function.
- Set its level to 5 using the appropriate setter functions
- Set its tame flag to True using the appropriate setter function.
- Print out the creature's information using the `display()` function:

  **Expected output:**
  ```
  NAMELESS
  Category: UNKNOWN
  Level: 5
  Hitpoints: 10
  Tame: TRUE
  ```

##### Task 2.2
- Instantiate a creature with the parameterized constructor with the following creature details:
  - Name: Wormy
  - Category: MYSTICAL
  - Level: 2
  - Hitpoints: 3
- Set Wormy as Tame with the appropriate setter function.
- Print out the creature's information using the `display()` function:

  **Expected output:**
  ```
  WORMY
  Category: MYSTICAL
  Level: 2
  Hitpoints: 3
  Tame: TRUE
  ```

### Submission
Submit via GitHub Classroom to Gradescope:
- `Creature.hpp`
- `Creature.cpp`
- `test.cpp`

### Compilation with Makefile
Use the command `make rebuild` to compile.

### Grading Rubrics
- Correctness: 80%
- Documentation: 15%
- Style and Design: 5%

### Due Date
Submit by 2/8. No late submissions accepted.

### Help
Drop-in tutoring available in Lab 1001B (see Blackboard for schedule).

---

### Authors
Georgina Woo, Tiziana Ligorio

For more details, refer to the full project description on [Project 1 Page](https://tligorio.github.io/projects/project1/Project-1.html).
