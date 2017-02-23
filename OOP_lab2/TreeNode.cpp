#include "TreeNode.h"
#include <iostream>

TTreeNode::TTreeNode(const Hexagon &hexagon) {
    this->hexagon = hexagon;
    for(int i = 0; i < N; i++){
        this->child[i] = nullptr;
    }
    std::cout << "Tree node: created" << std::endl;
}

TTreeNode::TTreeNode(const TTreeNode &orig) {
    this->hexagon = orig.hexagon;
    for(int i = 0; i < N; i++){
        this->child[i] = orig.child[i];
    }
    std::cout << "Tree node: copied" << std::endl;
}

Hexagon TTreeNode::GetHexagon() const {
    return Hexagon(hexagon);
}

TTreeNode::~TTreeNode() {
    std::cout << "Tree node: deleted" << std::endl;
    delete this;
}

std::ostream& operator<<(std::ostream &os, const TTreeNode &obj) {
    os << "[" << obj.GetHexagon() << "]" << std::endl;
    return os;
}