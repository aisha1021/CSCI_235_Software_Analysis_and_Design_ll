/*
Aisha Malik
aisha.malik46@myhunter.cuny.edu
Tiziana Ligorio
CSCI235 Spring 2024
Project 7 - Binary Skill Tree
*/

#include "SkillTree.hpp"

/**
  * Default Constructor
*/
SkillTree::SkillTree() : BinarySearchTree<Skill>() {}

/**
 * @param: A const reference to string: the name of a csv file
 * @post: The SkillTree is populated with Skills from the csv file
 * The file format is as follows:
 * id,name,description,leveled
 * Ignore the first line. Each subsequent line represents a Skill to be added to the SkillTree.
*/
SkillTree::SkillTree(const std::string& filename) : BinarySearchTree<Skill>() {
    std::ifstream file(filename); // open the file
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line; // skip the first line (header)
    std::getline(file, line);

    while (std::getline(file, line)) { // read each line and add Skill to the tree
        std::istringstream iss(line);
        std::string token;
        int id;
        std::string name, description;
        bool leveled;

        std::getline(iss, token, ','); // parse CSV fields
        id = std::stoi(token);

        std::getline(iss, name, ',');
        std::getline(iss, description, ',');
        std::getline(iss, token, ',');
        leveled = (token == "true");

        Skill skill(id, name, description, leveled); // create Skill object and add it to the tree
        addSkill(skill);
    }

    file.close();
}

/**
 * @param: A const reference to int representing the id of the Skill to be found
 * @return: A pointer to the node containing the Skill with the given id, or nullptr if the Skill is not found
*/
std::shared_ptr<BinaryNode<Skill>> SkillTree::findSkill(const int& id) const {
    std::shared_ptr<BinaryNode<Skill>> current_node = getRoot();
    Skill search_skill(id, "", "", false);
    while (current_node != nullptr) {
        if (current_node->getItem() == search_skill) {
            return current_node;
        } else if (current_node->getItem() > search_skill) {
            current_node = current_node->getLeftChildPtr();
        } else {
            current_node = current_node->getRightChildPtr();
        }
    }
    return nullptr; // skill not found
}

/**
  * @param: A const reference to Skill 
  * @post: The Skill is added to the tree (in BST order as implemented in the base class) only if it was not already in the tree. Note that all comparisons are id-based as implemented by the Skill comparison operators.
  * @return: True if the Skill is successfully added to the SkillTree, false otherwise
*/
bool SkillTree::addSkill(const Skill& skill) {
    if (!BinarySearchTree<Skill>::contains(skill)) {
        BinarySearchTree<Skill>::add(skill);
        return true; // skill added
    } else {
        return false; // skill already exists in the tree
    }
}

/**
  * @param: A const reference to string: the name of a Skill
  * @return: True if the Skill is successfully removed from the SkillTree, false otherwise
*/
bool SkillTree::removeSkill(const std::string& name) {
    std::shared_ptr<BinaryNode<Skill>> currentNode = getRoot(); // traverse tree to find the node containing the skill with the given name
    std::shared_ptr<BinaryNode<Skill>> parentNode = nullptr;
    while (currentNode != nullptr) {
        if (currentNode->getItem().name_ == name) {
            break; // found the node containing the skill with the given name
        } else if (currentNode->getItem().name_ > name) {
            parentNode = currentNode;
            currentNode = currentNode->getLeftChildPtr();
        } else {
            parentNode = currentNode;
            currentNode = currentNode->getRightChildPtr();
        }
    }

    if (currentNode == nullptr) {
        return false; // skill not found
    }

    if (parentNode == nullptr) { // use the BinarySearchTree remove function to remove the node
        BinarySearchTree<Skill>::remove(currentNode->getItem()); // node to be removed is the root
    } else if (parentNode->getLeftChildPtr() == currentNode) {
        parentNode->setLeftChildPtr(nullptr); // node to be removed is a left child
        BinarySearchTree<Skill>::remove(currentNode->getItem());
    } else {
        parentNode->setRightChildPtr(nullptr); // node to be removed is a right child
        BinarySearchTree<Skill>::remove(currentNode->getItem());
    }

    return true;
}


/**
  * @post: Clears the tree
*/
void SkillTree::clear() {
    root_ptr_ = nullptr;
}

/**
  * @param: A const reference to int representing the id of a Skill
    * Note: For a Skill to be leveled up, its parent Skill must also be leveled up, thus the Skill points are the number of Skills that must be leveled up before and including the Skill with the given id.
  * @return: an integer: the number of skill points needed to level up the Skill with the given id, starting from the root (i.e. the number of nodes from root to the given Skill).
  * Include the Skill with the given id in the count. For example, if the tree contains the following Skills (represented by their ids):
  *   5
  *  / \
  * 1   8
  * and the function parameter queries for id 8, the function should return 2.
  * Disregard the leveled_ field of the existing Skills in the tree.
  * If the Skill with the given id is not found, return -1.
*/
int SkillTree::calculateSkillPoints(const int& id) const {
    std::shared_ptr<BinaryNode<Skill>> skill_node = findSkill(id);
    if (skill_node == nullptr) return -1;
    int skill_points = 1; // include the root node
    std::shared_ptr<BinaryNode<Skill>> current_node = root_ptr_;
    while (current_node != nullptr && current_node->getItem().id_ != id) {
        if (current_node->getItem().id_ > id) {
            current_node = current_node->getLeftChildPtr();
        } else {
            current_node = current_node->getRightChildPtr();
        }
        skill_points++;
    }
    return skill_points;
}

/**
  * @post: Balances the tree. Recall the definition of a balanced tree:
  * A tree is balanced if for any node, its left and right subtrees differ in height by no more than 1. * All paths from root of subtrees to leaf differ in length by at most 1
  * Hint: You may sort the elements and build the tree recursively using a divide and conquer approach      
*/
void SkillTree::balance() {
    std::vector<Skill> sorted_skills; // collect all the nodes of the tree in sorted order
    inorderTraversal(root_ptr_, sorted_skills);

    root_ptr_ = buildBalancedTree(sorted_skills, 0, sorted_skills.size() - 1);  // rebuild the tree using the sorted nodes
}

/**
  * @post: prints the tree in preorder, in the format:
    [id_] [name_]\n
    [description_]\n 
    [leveled_]
*/
void SkillTree::preorderDisplay() {
    preorderTraverse(getRoot(), [](const Skill& skill) {
        std::cout << skill.id_ << skill.name_ << "\n";
        std::cout << skill.description_ << "\n";
        std::cout << (skill.leveled_ ? 1 : 0) << "\n\n";
    });
}

/**
 * @param node A pointer to the current node being traversed
 * @param sorted_skills A reference to a vector to store the sorted skills
 * @post Performs an inorder traversal of the binary tree starting from the given node and stores the skills in sorted order in the provided vector
 */
void SkillTree::inorderTraversal(std::shared_ptr<BinaryNode<Skill>> node, std::vector<Skill>& sorted_skills) const {
    if (node != nullptr) {
        inorderTraversal(node->getLeftChildPtr(), sorted_skills);
        sorted_skills.push_back(node->getItem());
        inorderTraversal(node->getRightChildPtr(), sorted_skills);
    }
}

/**
 * @param sorted_skills A vector containing skills sorted in ascending order
 * @param start The starting index of the subarray
 * @param end The ending index of the subarray
 * @return A pointer to the root of the balanced binary tree
 * @post Builds a balanced binary tree from the provided vector of skills using a divide and conquer approach
 */
std::shared_ptr<BinaryNode<Skill>> SkillTree::buildBalancedTree(const std::vector<Skill>& sorted_skills, int start, int end) const {
    if (start > end) {
        return nullptr;
    }

    int mid = (start + end) / 2;
    std::shared_ptr<BinaryNode<Skill>> root = std::make_shared<BinaryNode<Skill>>(sorted_skills[mid]);
    root->setLeftChildPtr(buildBalancedTree(sorted_skills, start, mid - 1));
    root->setRightChildPtr(buildBalancedTree(sorted_skills, mid + 1, end));
    return root;
}

/**
 * @param node A pointer to the current node being traversed
 * @param action A function to be applied to each skill during traversal
 * @post Performs a preorder traversal of the binary tree starting from the given node and applies the specified action to each skill node
 */
void SkillTree::preorderTraverse(std::shared_ptr<BinaryNode<Skill>> node, std::function<void(const Skill&)> action) const {
    if (node != nullptr) {
        action(node->getItem());
        preorderTraverse(node->getLeftChildPtr(), action);
        preorderTraverse(node->getRightChildPtr(), action);
    }
}