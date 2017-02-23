#ifndef OOP_LAB2_TREE_H
#define OOP_LAB2_TREE_H

#include "TreeNode.h"
#include "Hexagon.h"

class TTree {
public:
    TTree();
    TTree(const TTree& orig);
    void goThrough(const TTree& tTree)const;
    void add(Hexagon &&hexagon);
    bool empty();
    Hexagon deleteNode();
    void setRoot(Hexagon &&hexagon);
    Hexagon getNode();

    friend std::ostream& operator<<(std::ostream& os, const TTree& tTree);

    virtual ~TTree();
private:
    TTreeNode *root;
};


#endif
