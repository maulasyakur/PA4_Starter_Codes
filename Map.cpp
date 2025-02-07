#include "Map.h"

Map::Map()
{
    this->root = nullptr;
}
Map::~Map()
{
    // TODO: Free any dynamically allocated memory if necessary
    std::queue<MapNode *> queue;
    queue.push(root);
    while(!queue.empty()){
        MapNode *curr = queue.front();
        if (curr->right != nullptr){
            queue.push(curr->right);
        }
        if (curr->left != nullptr){
            queue.push(curr->left);
        }
        queue.pop();
        delete curr;
    }
}

void Map::initializeMap(std::vector<Isle *> isles)
{
    // TODO: Insert innitial isles to the tree
    // Then populate with Goldium and Einstainium items
    for (Isle * isle : isles){
        root = insert(root, isle);
    }
}

MapNode *Map::rotateRight(MapNode *current)
{
    // TODO: Perform right rotation according to AVL
    // return necessary new root
    // Use std::cerr << "[Right Rotation] " << "Called on invalid node!" << std::endl;
    if (current->left == nullptr){
        std::cerr << "[Right Rotation] " << "Called on invalid node!" << std::endl;    
    }

    MapNode *x = current->left;
    MapNode *T2 = x->right;

    // Perform rotation
    x->right = current;
    current->left = T2;

    // Update heights
    current->height = std::max(height(current->left), height(current->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

MapNode *Map::rotateLeft(MapNode *current)
{
    // TODO: Perform left rotation according to AVL
    // return necessary new root
    // Use std::cerr << "[Left Rotation] " << "Called on invalid node!" << std::endl;
    if (current->right == nullptr){
        std::cerr << "[Left Rotation] " << "Called on invalid node!" << std::endl;
    }

    MapNode *y = current->right;
    MapNode *T2 = y->left;

    // Perform rotation
    y->left = current;
    current->right = T2;

    //  Update heights
    current->height = std::max(height(current->left), height(current->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

int calculateMinMapDepthAccess(int playerDepth, int totalShaperTreeHeight, int totalMapDepth)
{
    return (int)totalMapDepth * ((double)playerDepth / totalShaperTreeHeight);
}

int Map::height(MapNode *node)
{
    // TODO: Return height of the node
    if (node == nullptr){
        return 0;
    }

    return node->height;
}

MapNode *Map::insert(MapNode *node, Isle *isle)
{
    // TODO: Recursively insert isle to the tree
    // returns inserted node

    /* 1.  Perform the normal BST insertion */
    if (node == nullptr)
        return new MapNode(isle);

    if (isle < node->isle)
        node->left = insert(node->left, isle);
    else if (isle > node->isle)
        node->right = insert(node->right, isle);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + std::max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
    int balance = height(node->left) - height(node->right);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && isle < node->left->isle)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && isle > node->right->isle)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && isle > node->left->isle)
    {
        node->left =  rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && isle < node->right->isle)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

void Map::insert(Isle *isle)
{
    root = insert((root), isle);

    // you might need to insert some checks / functions here depending on your implementation
}

MapNode *Map::remove(MapNode *node, Isle *isle)
{
    // TODO: Recursively delete isle from the tree
    // Will be called if there is overcrowding
    // returns node
    // Use std::cout << "[Remove] " << "Tree is Empty" << std::endl;
    
    // // Check for an empty tree
    // if (node == nullptr) {
    //     std::cout << "[Remove] Tree is Empty" << std::endl;
    //     return nullptr;
    // }

    // // Perform standard BST delete
    // if (*isle < *(node->isle)) {
    //     node->left = remove(node->left, isle);
    // } else if (*isle > *(node->isle)) {
    //     node->right = remove(node->right, isle);
    // } else {
    //     // Node with only one child or no child
    //     if ((node->left == nullptr) || (node->right == nullptr)) {
    //         MapNode* temp = node->left ? node->left : node->right;
    //         delete node; // Delete the current node
    //         return temp; // Return the single child or nullptr
    //     } else {
    //         // Node with two children: Find the in-order successor
    //         MapNode* temp = node->right;
    //         while (temp->left != nullptr)
    //             temp = temp->left;

    //         // Replace node's isle with successor's isle
    //         delete node->isle; // Free the old isle
    //         node->isle = temp->isle;

    //         // Delete the in-order successor
    //         node->right = remove(node->right, temp->isle);
    //     }
    // }

    // // Update height of the current node
    // node->height = 1 + std::max(height(node->left), height(node->right));

    // // Get the balance factor of this node
    // int balance = height(node->left) - height(node->right);

    // // Balance the node
    // if (balance > 1 && node->left && height(node->left->left) - height(node->left->right) >= 0)
    //     return rotateRight(node);

    // if (balance > 1 && node->left && height(node->left->left) - height(node->left->right) < 0) {
    //     node->left = rotateLeft(node->left);
    //     return rotateRight(node);
    // }

    // if (balance < -1 && node->right && height(node->right->left) - height(node->right->right) <= 0)
    //     return rotateLeft(node);

    // if (balance < -1 && node->right && height(node->right->left) - height(node->right->right) > 0) {
    //     node->right = rotateRight(node->right);
    //     return rotateLeft(node);
    // }

    // return node;
}

void Map::remove(Isle *isle)
{
    root = remove((root), isle);
    // you might need to insert some checks / functions here depending on your implementation
}

void Map::preOrderItemDrop(MapNode *current, int &count)
{
    // TODO: Drop EINSTEINIUM according to rules
    // Use std::cout << "[Item Drop] " << "EINSTEINIUM dropped on Isle: " << current->isle->getName() << std::endl;
}

// to Display the values by Post Order Method .. left - right - node
void Map::postOrderItemDrop(MapNode *current, int &count)
{
    // TODO: Drop GOLDIUM according to rules
    // Use  std::cout << "[Item Drop] " << "GOLDIUM dropped on Isle: " << current->isle->getName() << std::endl;
}

MapNode *Map::findFirstEmptyIsle(MapNode *node)
{
    // TODO: Find first Isle with no item
}

void Map::dropItemBFS()
{
    // TODO: Drop AMAZONITE according to rules
    // Use std::cout << "[BFS Drop] " << "AMAZONITE dropped on Isle: " << targetNode->isle->getName() << std::endl;
    // Use std::cout << "[BFS Drop] " << "No eligible Isle found for AMAZONITE drop." << std::endl;
}

void Map::displayMap()
{
    std::cout << "[World Map]" << std::endl;
    display(root, 0, 0);
}

int Map::getDepth(MapNode *node)
{
    // TODO: Return node depth if found, else
    MapNode *ptr = root;
    while (ptr != nullptr){
        if (*ptr->isle == *node->isle){
            return ptr->height;
        } else if (*ptr->isle < *node->isle){
            ptr = ptr->right;
        } else if (*ptr->isle > *node->isle){
            ptr = ptr->left;
        }
    }

    return -1;
}

// Function to calculate the depth of a specific node in the AVL tree
int Map::getIsleDepth(Isle *isle)
{
    // TODO: Return node depth by isle if found, else
    MapNode *ptr = root;
    while (ptr != nullptr){
        if (*ptr->isle == *isle){
            return ptr->height;
        } else if (*ptr->isle < *isle){
            ptr = ptr->right;
        } else if (*ptr->isle > *isle){
            ptr = ptr->left;
        }
    }

    return -1;
}

int Map::getDepth()
{
    // TODO: Return max|total depth of tree
    if (root == nullptr){
        return -1;
    }

    MapNode *ptr = root;
    std::queue<MapNode*> queue;
    queue.push(ptr);
    int height = 0;
    while (!queue.empty()){
        MapNode *curr_map_node = queue.front();
        queue.push(curr_map_node->right);
        queue.push(curr_map_node->left);
        if (height < curr_map_node->height){ // stores the maximum height
            height = curr_map_node->height;
        }
        queue.pop();
    }

    return height;
}

void Map::populateWithItems()
{
    // TODO: Distribute fist GOLDIUM than EINSTEINIUM
}

Isle *Map::findIsle(Isle isle)
{
    // TODO: Find isle by value
    MapNode *ptr = root;
    while (ptr != nullptr){
        if (*ptr->isle == isle){
            return ptr->isle;
        } else if (*ptr->isle < isle){
            ptr = ptr->right;
        } else if (*ptr->isle > isle){
            ptr = ptr->left;
        }
    }

    return nullptr;
}

Isle *Map::findIsle(std::string name)
{
    // TODO: Find isle by name
    Isle isle(name);
    MapNode *ptr = root;
    while (ptr != nullptr){
        if (*ptr->isle == isle){
            return ptr->isle;
        } else if (*ptr->isle < isle){
            ptr = ptr->right;
        } else if (*ptr->isle > isle){
            ptr = ptr->left;
        }
    }
    return nullptr;
}

MapNode *Map::findNode(Isle isle)
{
    // TODO: Find node by value
    MapNode *ptr = root;
    while (ptr != nullptr){
        if (*ptr->isle == isle){
            return ptr;
        } else if (*ptr->isle < isle){
            ptr = ptr->right;
        } else if (*ptr->isle > isle){
            ptr = ptr->left;
        }
    }
    return nullptr;
}

MapNode *Map::findNode(std::string name)
{
    // TODO: Find node by name
    Isle isle(name);
    MapNode *ptr = root;
    while (ptr != nullptr){
        if (*ptr->isle == isle){
            return ptr;
        } else if (*ptr->isle < isle){
            ptr = ptr->right;
        } else if (*ptr->isle > isle){
            ptr = ptr->left;
        }
    }
    return nullptr;
}

void Map::display(MapNode *current, int depth, int state)
{
    // SOURCE:

    if (current->left)
        display(current->left, depth + 1, 1);

    for (int i = 0; i < depth; i++)
        printf("     ");

    if (state == 1) // left
        printf("   ┌───");
    else if (state == 2) // right
        printf("   └───");

    std::cout << "[" << *current->isle << "] - (" << current->height << ")\n"
              << std::endl;

    if (current->right)
        display(current->right, depth + 1, 2);
}

void Map::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output level by level
}

void Map::writeIslesToFile(const std::string &filename)
{
    // TODO: Write Isles to output file in alphabetical order
    // Use std::cout << "[Output] " << "Isles have been written to " << filename << " in in alphabetical order." << std::endl;
}