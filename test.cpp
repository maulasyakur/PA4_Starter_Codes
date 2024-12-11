#include "RealmShaper.h"
#include "RealmShapers.h"

int main(int argc, char const *argv[])
{
    std::vector<RealmShaper *> realmShapers = RealmShaper::readFromFile("io/initial_realm_shapers.txt");
    ShaperTree tree;
    tree.initializeTree(realmShapers);
    tree.remove(realmShapers[1]);
    return 0;
}
