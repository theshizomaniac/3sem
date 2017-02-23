#include <iostream>
#include <cstdlib>

#include "Hexagon.h"
#include "TreeNode.h"
#include "Tree.h"

int main() {
    TTree *tTree;
    std::cout << "a" << std::endl;
    tTree->setRoot(Hexagon(1));
    std::cout << "b" << std::endl;
    tTree->add(Hexagon(2));std::cout << "c" << std::endl;
    tTree->add(Hexagon(3));
    tTree->add(Hexagon(5));

    tTree->getNode();
    tTree->getNode();

    std::cout << tTree;

    tTree->deleteNode();
    tTree->deleteNode();

    std::cout << tTree;

    delete tTree;
}
