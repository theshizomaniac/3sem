

#ifndef DA2_NODE_H
#define DA2_NODE_H

//#include "data.h"

#include <fstream>


class TNode {
    friend class TRedBlackTree;
public:
    //TNode * parent;
    //TData key;
    TNode();
    TNode(char * data, unsigned long long key, int);
     ~TNode();
    unsigned long long GetKey();
protected:
    int red; /* if red = 0 then the node is black */
    TNode * left;
    TNode * right;
    TNode * parent;
    unsigned long long key;
    char * word;
};

class TRedBlackTree {
public:
    TRedBlackTree();
    ~TRedBlackTree();
    void PrintTree();
    void Print(TNode *) const;
    void DeleteNode(TNode *);
    TNode * Insert(char*, unsigned long long, int);
    TNode * Search(char*);
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
