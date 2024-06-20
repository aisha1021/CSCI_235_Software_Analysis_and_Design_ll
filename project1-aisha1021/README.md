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

### Task 1: Implement `Creature` Class
- Follow the specifications strictly.
- Ensure all names, parameters, and returns match exactly.

### Task 2: Testing
Submit `test.cpp` with:
- Test cases for both default and parameterized constructors.
- Use `set` functions to modify attributes.
- Use `display()` to verify output.

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

---

For more details, refer to the full project description on [Project 1 Page](https://tligorio.github.io/projects/project1/Project-1.html).
