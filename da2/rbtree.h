//
// Created by mrhacker on 10/23/16.
//

#ifndef DA2_NODE_H
#define DA2_NODE_H

#include "data.h"
#include <fstream>

class TNode {
    friend class TRedBlackTree;
public:
    TNode * parent;
    TData key;
    TNode();
    TNode(std::istream&);
    TNode(TData);
    ~TNode();
protected:
    int red; /* if red = 0 then the node is black */
    TNode * left;
    TNode * right;
    //TNode * parent;
};

class TRedBlackTree {
public:
    TRedBlackTree();
    virtual ~TRedBlackTree();
    void PrintTree();
    void Print(TNode *) const;
    TData DeleteNode(TNode *);
    TNode * Insert(TData);
    TNode * Search(TData);
    TNode * GetPredecessorOf(TNode *) const;
    TNode * GetSuccessorOf(TNode *) const;
    bool Serialize(char *);
    bool Deserialize(char *);

protected:
    TNode * root;
    TNode * nil;

    bool readErrors;

    void SerializeRec (TNode*, std::ostream&);
    TNode * DeserializeRec (TNode *, std::istream&);

    void Destruction(TNode *);
    void LeftRotate(TNode *);
    void RightRotate(TNode *);
    bool BinInsert(TNode *);
    void DeleteFixUp(TNode *);
};

#endif //DA2_NODE_H
