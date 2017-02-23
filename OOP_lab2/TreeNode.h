//
// Created by ayy on 11/8/16.
//

#ifndef TREENODE_H
#define TREENODE_H
#include "Hexagon.h"
#define N 5

class TTreeNode {
public:
    TTreeNode(const Hexagon& hexagon);
    TTreeNode(const TTreeNode& orig);
    friend std::ostream& operator<<(std::ostream& os, const TTreeNode &obj);

    Hexagon GetHexagon() const;

    virtual ~TTreeNode();

    TTreeNode *child[N];
private:
    Hexagon hexagon;
};

#endif
