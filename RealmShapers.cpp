#include "RealmShapers.h"
#include <cmath>
#include <algorithm>

ShaperTree::ShaperTree()
{
}

ShaperTree::~ShaperTree()
{
    // TODO: Free any dynamically allocated memory if necessary
    for (RealmShaper *realm_shaper : realmShapers){
        delete realm_shaper;
    }
}

void ShaperTree::initializeTree(std::vector<RealmShaper *> shapers)
{
    // TODO: Insert innitial shapers to the tree
    realmShapers = shapers;
}

int ShaperTree::getSize()
{
    // TODO: Return number of shapers in the tree
    return realmShapers.size();
}

std::vector<RealmShaper *> ShaperTree::getTree()
{
    return realmShapers;
}

bool ShaperTree::isValidIndex(int index)
{
    // TODO: Check if the index is valin in the tree
    if (index < realmShapers.size() && realmShapers[index] != nullptr){
        return true;
    }

    return false;
}

void ShaperTree::insert(RealmShaper *shaper)
{
    // TODO: Insert shaper to the tree
    // int index = 0;
    // while (index < realmShapers.size()){
    //     if (shaper < realmShapers[index]){
    //         index = index * 2 + 1;
    //     } else if (shaper > realmShapers[index]){
    //         index = index * 2 + 2;
    //     } else {
    //         return; // two same players cannot exist
    //     }
    // }
    realmShapers.push_back(shaper);
}

int ShaperTree::remove(RealmShaper *shaper)
{
    // TODO: Remove the player from tree if it exists
    // Make sure tree protects its form (complate binary tree) after deletion of a node
    // return index if found and removed
    // else return -1

    // find the index
    int index = findIndex(shaper);
    if (index == -1){
        return -1;
    }

    // free from memory
    delete realmShapers[index];
    realmShapers.erase(realmShapers.begin() + index);

    // // shift the elements left
    // for (int i = index; i < realmShapers.size() - 1; i++){
    //     realmShapers[i] = realmShapers[i + 1];
    // }

    return index;
}

int ShaperTree::findIndex(RealmShaper *shaper)
{
    // return index in the tree if found
    for (int i = 0; i < realmShapers.size(); i++){
        if (realmShapers[i] == shaper){
            return i;
        }
    }

    // else
    return -1;
}

int ShaperTree::getDepth(RealmShaper *shaper)
{
    // find the index
    int index = findIndex(shaper);
    if (index == -1){
        return -1;
    }

    // shaper is in the tree
    return (int) log(index + 1) / log(2);
}

int ShaperTree::getDepth()
{
    // return total|max depth|height of the tree
    return (int) log(realmShapers.size()) / log(2);
}

RealmShaper ShaperTree::duel(RealmShaper *challenger, bool result)
{
    // TODO: Implement duel logic, return the victor
    // Use   std::cout << "[Duel] " << victorName << " won the duel" << std::endl;
    // Use   std::cout << "[Honour] " << "New honour points: ";
    // Use   std::cout << challengerName << "-" << challengerHonour << " ";
    // Use   std::cout << opponentName << "-" << opponentHonour << std::endl;
    // Use   std::cout << "[Duel] " << loserName << " lost all honour, delete" << std::endl;
}

RealmShaper *ShaperTree::getParent(RealmShaper *shaper)
{
    // TODO: return parent of the shaper
    int index = findIndex(shaper);
    if (index % 2 == 0){ // if node is on the right
        index = (index - 2) / 2;
        return realmShapers[index];
    } else { // if node is on the 
        index = (index - 1) / 2;
        return realmShapers[index];
    }

    return nullptr;
}

void ShaperTree::replace(RealmShaper *player_low, RealmShaper *player_high)
{
    // TODO: Change player_low and player_high's positions on the tree
    RealmShaper *temp = player_high;
    player_high = player_low;
    player_low = temp;
}

RealmShaper *ShaperTree::findPlayer(RealmShaper shaper)
{
    // TODO: Search shaper by object
    // Return the shaper if found
    // Return nullptr if shaper not found
    for(int i = 0; i < realmShapers.size(); i++){
        if (*realmShapers[i] == shaper){
            return realmShapers[i];
        }
    }

    return nullptr;
}

// Find shaper by name
RealmShaper *ShaperTree::findPlayer(std::string name)
{
    // TODO: Search shaper by name
    // Return the shaper if found
    // Return nullptr if shaper not found
    for(int i = 0; i < realmShapers.size(); i++){
        if (realmShapers[i]->getName() == name){
            return realmShapers[i];
        }
    }

    return nullptr;
}

std::vector<std::string> ShaperTree::inOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement inOrderTraversal in tree
    // Add all to a string vector
    // Return the vector

    // Define and implement as many helper functions as necessary for recursive implementation

    // Note: Since SheperTree is not an binary search tree,
    // in-order traversal will not give rankings in correct order
    // for correct order you need to implement level-order traversal
    // still you are to implement this function as well
    return result;
}

std::vector<std::string> ShaperTree::preOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement preOrderTraversal in tree
    // Add all to a string vector
    // Return the vector

    // Define and implement as many helper functions as necessary for recursive implementation
    return result;
}

std::vector<std::string> ShaperTree::postOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement postOrderTraversal in tree
    // Add all to a string vector
    // Return the vector

    // Define and implement as many helper functions as necessary for recursive implementation
    return result;
}

void ShaperTree::preOrderTraversal(int index, std::ofstream &outFile)
{
    // TODO: Implement preOrderTraversal in tree
    // write nodes to output file

    // Define and implement as many helper functions as necessary for recursive implementation
}

void ShaperTree::breadthFirstTraversal(std::ofstream &outFile)
{
    // TODO: Implement level-order traversal
    // write nodes to output file

    // Define and implement as many helper functions as necessary
}

void ShaperTree::displayTree()
{
    std::cout << "[Shaper Tree]" << std::endl;
    printTree(0, 0, "");
}

// Helper function to print tree with indentation
void ShaperTree::printTree(int index, int level, const std::string &prefix)
{
    if (!isValidIndex(index))
        return;

    std::cout << prefix << (level > 0 ? "   └---- " : "") << *realmShapers[index] << std::endl;
    int left = 0;  // TODO: Calculate left index
    int right = 0; // TODO: Calculate right index

    if (isValidIndex(left) || isValidIndex(right))
    {
        printTree(left, level + 1, prefix + (level > 0 ? "   │   " : "")); // ╎
        printTree(right, level + 1, prefix + (level > 0 ? "   │   " : ""));
    }
}

void ShaperTree::writeShapersToFile(const std::string &filename)
{
    // TODO: Write the shapers to filename output level by level
    // Use std::cout << "[Output] " << "Shapers have been written to " << filename << " according to rankings." << std::endl;
}

void ShaperTree::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output pre-order
    // Use std::cout << "[Output] " << "Tree have been written to " << filename << " in pre-order." << std::endl;
}
